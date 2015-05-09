#include <xc.h>

#include <stdint.h>        /* Includes uint16_t definition   */
#include <stdbool.h>       /* Includes true/false definition */
#include <stdio.h>
#include <stdlib.h>
#include <timer.h>
#include <uart.h>

//#include "extern_globals.h"

#include "lib_asserv/lib_asserv.h"
#include "user.h"
#include <libpic30.h>
#include "motor.h"
#include "ultrason.h"
// #include "motion.h"

//#include "tests.h"
//#include "lib_asserv/lib_asserv.h"
//#include "ax12.h"
//#include "atp-asserv.h"
//#include "actions_ax12.h"


char msg[16]="";

volatile int tics_d=0;
volatile int tics_g=0;
int tics_d_old=0;
int tics_g_old=0;

float V_d=0;
float V_g=0;

int erreur_d = 0;
int erreur_g = 0;

float Vcons_d=0;
float Vcons_g=0;

int somme_erreur_d = 0 ;
int somme_erreur_g = 0 ;

int erreur_d_old = 0;
int erreur_g_old = 0;

int var_erreur_d = 0;
int var_erreur_g = 0;

float commande_d = 0;
float commande_g = 0;

float Kp=11;
float Ki=2.3;
float Kd=0;

extern int reset_asserv;

volatile char UltraSon_Detect = 0;

void InitTimers()
{
    TRISBbits.TRISB7=1; //Pin RB7 en entr�e pour les AX12
    _ODCB7 = 1; // Open drain sur la pin RB7(pour les AX12)
    _NSTDIS = 0; // activation de la priorité des interruptions
    AD1PCFGL = 0xFFFF; //Pins analogiques en numérique pour que ATP marche !!


    OpenUART2(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW
        & UART_UEN_00 & UART_DIS_WAKE & UART_DIS_LOOPBACK
        & UART_DIS_ABAUD & UART_UXRX_IDLE_ONE & UART_BRGH_SIXTEEN
        & UART_NO_PAR_8BIT & UART_1STOPBIT,
          UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO
        & UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE & UART_TX_BUF_NOT_FUL & UART_INT_RX_CHAR
        & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR,
          BRGVALAX12);

    ConfigIntUART2(UART_RX_INT_PR5 & UART_RX_INT_EN
                 & UART_TX_INT_PR5 & UART_TX_INT_DIS);

    OpenUART1(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW
        & UART_UEN_00 & UART_DIS_WAKE & UART_DIS_LOOPBACK
        & UART_DIS_ABAUD & UART_UXRX_IDLE_ONE & UART_BRGH_SIXTEEN
        & UART_NO_PAR_8BIT & UART_1STOPBIT,
          UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO
        & UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE & UART_TX_BUF_NOT_FUL & UART_INT_RX_CHAR
        & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR,
          BRGVALAX12);


    ConfigIntUART1(UART_RX_INT_PR6 & UART_RX_INT_EN
                 & UART_TX_INT_PR6 & UART_TX_INT_DIS);


    // activation du Timer2
    OpenTimer2(T2_ON &
                T2_IDLE_CON &
                T2_GATE_OFF &
                T2_PS_1_64 &
                T2_SOURCE_INT, 15625 ); // 625 * x => x ms
    // configuration des interruptions
    ConfigIntTimer2(T2_INT_PRIOR_4 & T2_INT_ON);
    // Ici interruption des actions des bras
    //IFS2bits.SPI2IF = 0; // Flag SPI2 Event Interrupt Priority
    //IPC8bits.SPI2IP = 2; // Priority SPI2 Event Interrupt Priority
    //IEC2bits.SPI2IE = 1; //Enable SPI2 Event Interrupt Priority

    //Remapage uart 1
    _U1RXR = 18;
    _RP4R = 0b0011;  // RP4 = U1TX (p.167)



}

void Init_CN()
{
    _TRISA9 = 1;  // input for button
    _TRISC3 = 1;  // input for laisse
    _TRISC9 = 1;  // input for motor sensor
    _TRISC8 = 1;  // input for motor sensor

    _CN28IE = 1; // Enable CN28 pin for interrupt detection
    _CN20IE = 1; // Enable CN20 pin for interrupt detection (motor sensor)
    _CN19IE = 1; // Enable CN19 pin for interrupt detection (motor sensor)

    IPC4bits.CNIP = 6; //Interrupt level 3
    IEC1bits.CNIE = 1; // Enable CN interrupts
    IFS1bits.CNIF = 0; // Reset CN interrupt
}

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* TODO Add interrupt routine code here. */

void __attribute__((interrupt,auto_psv)) _T2Interrupt(void) {

    ////////////////// RESET DE L'ASSERV ENTRE DEUX COMMANDES //////////////////
    if (reset_asserv==1)
    {
        tics_d=0;
        tics_g=0;
        tics_d_old=0;
        tics_g_old=0;

        V_d=0;
        V_g=0;

        erreur_d = 0;
        erreur_g = 0;

        Vcons_d=0;
        Vcons_g=0;

        somme_erreur_d = 0 ;
        somme_erreur_g = 0 ;

        erreur_d_old = 0;
        erreur_g_old = 0;

        var_erreur_d = 0;
        var_erreur_g = 0;

        commande_d = 0;
        commande_g = 0;
    }
    ////////////////////////////////////////////////////////////////////////////


    ////////////////// ACQUISITION NOUVELLE VALEUR DE VITESSE //////////////////
    //        On suppose que les moteurs tournent dans le sens demand�        //
    if (Vcons_d>=0)  V_d = tics_d - tics_d_old;
    else            V_d = -(tics_d - tics_d_old);

    if (Vcons_g>=0) V_g = tics_g - tics_g_old;
    else            V_g = -(tics_g - tics_g_old);
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////// ACQUISITION NOUVELLE POSITION ///////////////////////
    tics_d_old=tics_d;
    tics_g_old=tics_g;
    ////////////////////////////////////////////////////////////////////////////

    /////////////// ERREURS DE VITESSE PAR RAPPORT A LA CONSIGNE ///////////////
    erreur_d = Vcons_d - V_d;
    erreur_g = Vcons_g - V_g;
    ////////////////////////////////////////////////////////////////////////////

    ////////////// SOMME DES ERREURS DE VITESSE POUR INTEGRATION ///////////////
    somme_erreur_d += erreur_d;
    somme_erreur_g += erreur_g;
    ////////////////////////////////////////////////////////////////////////////

    //////// DIFFERENCE DES DERNIERES ERREURS DE VITESSE POUR DERIVATION ///////
    var_erreur_d = erreur_d - erreur_d_old;
    var_erreur_g = erreur_g - erreur_g_old;
    ////////////////////////////////////////////////////////////////////////////

    //////////// COMMANDE PROPOTIONNELLE, INTEGRALE, DERIVEE (PID)  ////////////
    commande_d = Kp*erreur_d + Ki*somme_erreur_d + Kd*var_erreur_d;
    commande_g = Kp*erreur_g + Ki*somme_erreur_g + Kd*var_erreur_g;
    ////////////////////////////////////////////////////////////////////////////

    /////////////////// ACTUALISATION DE L'ERREUR PRECEDENTE ///////////////////
    erreur_d_old = erreur_d;
    erreur_g_old = erreur_g;
    ////////////////////////////////////////////////////////////////////////////

/*
    if (commande_g>0) MOTOR_BREAK1=0;
    else MOTOR_BREAK1=1;
    if (commande_d>0) MOTOR_BREAK2=0;
    else MOTOR_BREAK2=1;
*/
    PWM_Moteurs(commande_g, commande_d);

    //printf("erreur_g%d erreur_d%d \n\r",erreur_g,erreur_d);
    //printf("TicsG%d TicsD%d \n\r",tics_g,tics_d);
    //printf("diff_g%f diff_d%f \n\r",diff_g,diff_d);

    //printf("diff_cons_g_I%f diff_cons_d_I%f \n\r",diff_cons_g_I,diff_cons_d_I);
    _T2IF = 0;    // on baisse le flag
}

/*************************************************
*                 TX et RX Interrupt             *
*************************************************/
void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void){
    _U2RXIF = 0; // On baisse le FLAG
//    InterruptAX();
}

void __attribute__((__interrupt__, no_auto_psv)) _U2TXInterrupt(void){
   _U2TXIF = 0; // clear TX interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void){
    _U1RXIF = 0; // On baisse le FLAG
}

void __attribute__((__interrupt__, no_auto_psv)) _U1TXInterrupt(void){
    _U1TXIF = 0; // clear TX interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _SPI2Interrupt(void){
    led=1;
    IFS2bits.SPI2IF = 0;


}

/**********************************************/
/* CN interrupt for boutons and motor sensor  */
/**********************************************/

void __attribute__ ((__interrupt__, no_auto_psv)) _CNInterrupt(void)
{
    static char lastMotorStateL = 0;
    static char lastMotorStateR = 0;
    static char last_Etat_Pin_Laisse = 0;


    IFS1bits.CNIF = 0; // Clear CN interrupt
    char Etat_Pin_Laisse = PIN_LAISSE;
    char Etat_Pin_Sensor_L = MOT_SENSOR_PIN_L;
    char Etat_Pin_Sensor_R = MOT_SENSOR_PIN_R;
    uint8_t Etat_Pin_Ultrason = PIN_ULTRASON;
    uint32_t val32;

    if (Etat_Pin_Laisse != last_Etat_Pin_Laisse) {
        last_Etat_Pin_Laisse = Etat_Pin_Laisse;
        if (!Etat_Pin_Laisse) {
            // mettre commande start
        } else {
            __delay_ms(50);
        }
    }

    if (Etat_Pin_Sensor_L != lastMotorStateL) {
        lastMotorStateL=Etat_Pin_Sensor_L;
        tics_g ++;
    }
    if (Etat_Pin_Sensor_R != lastMotorStateR) {
        lastMotorStateR=Etat_Pin_Sensor_R;
        tics_d ++;
    }


    // si Etat_Ultrason m�rite que l'on s'occupe de lui
    if (Etat_Ultrason & (U_ETAT_WAIT1 + U_ETAT_WAIT0 + U_ETAT_WAIT0_OVERSHOOT)) {
        if (Etat_Pin_Ultrason) {
            if (Etat_Ultrason & U_ETAT_WAIT1) {
                //if (!count_Debug_Ultrason && Debug_Ultrason) { printf("$START_MESURE;"); }
                TMR4 = 0;                       // restart du timer pour la mesure
                Etat_Ultrason = U_ETAT_WAIT0;
            }
        } else {
            if (Etat_Ultrason & U_ETAT_WAIT0) {     // si attente standard => r�cup mesure
                PIN_CN_ULTRASON_IE = 0;     // desactivation de cette IT
                Mesure_Timer_Ultrason = TMR4;       // 1 = 0.2us
                //if (!count_Debug_Ultrason && Debug_Ultrason) { printf("$END_MESURE;"); }
                // � base de vitesse du son (/2 pour l'aller-retour)  340.29 m/s
                // => 1 coup = 34 us
                // pour avoir distance en mm, il faut diviser par 29.39
                // donc multiplication par 1115 puis division par 32768 (2^15)
                // passage oblig� en 32 bits
                val32 = 1115 * (uint32_t)(Mesure_Timer_Ultrason);
                Mesure_Distance_Ultrason = (uint16_t)((val32 >> 15));
                if (Sector_Ultrason) {
                    if (Mesure_Distance_Ultrason < (ULTRASON_THRESOLD - ULTRASON_THRESOLD_TRIGGER)) {
                        //motion_free();
                        UltraSon_Detect = 1;
                        Sector_Ultrason = 0;            // passage en sector  occup�
                        //DetectUltrason();		// on previent la PI  // pas de PI sur tarant'
                    }
                } else {
                    if (Mesure_Distance_Ultrason > (ULTRASON_THRESOLD + ULTRASON_THRESOLD_TRIGGER)) {
                        UltraSon_Detect = 0;
                        Sector_Ultrason = 1;    // passage en sector ok
                        //ReleaseUltrason();              // on previent la PI  // pas de PI sur tarant'
                    }
                }
                Etat_Ultrason = U_ETAT_WAIT_FOR_RESTART;   // attente fin du timer pour restart...
            } else if (Etat_Ultrason & U_ETAT_WAIT0_OVERSHOOT) {    // si attente overshoot => fabrication d'une mesure max
                //if (!count_Debug_Ultrason && Debug_Ultrason) { printf("$END_MESURE_OVER;"); }
                PIN_CN_ULTRASON_IE = 0;     // desactivation de cette IT
                Mesure_Timer_Ultrason = 0xFFFF;
                Mesure_Distance_Ultrason = 3000;            // 3m
                Etat_Ultrason = U_ETAT_WAIT_FOR_RESTART;    // attente fin du timer pour restart...
            }
        }
    }

    //printf("TicsG%d TicsD%d \n\r",tics_g,tics_d);

}



/******************************************************************************/
/* Interrupt Vector Options                                                   */
/******************************************************************************/
/*                                                                            */
/* Refer to the C30 (MPLAB C Compiler for PIC24F MCUs and dsPIC33F DSCs) User */
/* Guide for an up to date list of the available interrupt options.           */
/* Alternately these names can be pulled from the device linker scripts.      */
/*                                                                            */
/* dsPIC33F Primary Interrupt Vector Names:                                   */
/*                                                                            */
/* _INT0Interrupt      _C1Interrupt                                           */
/* _IC1Interrupt       _DMA3Interrupt                                         */
/* _OC1Interrupt       _IC3Interrupt                                          */
/* _T1Interrupt        _IC4Interrupt                                          */
/* _DMA0Interrupt      _IC5Interrupt                                          */
/* _IC2Interrupt       _IC6Interrupt                                          */
/* _OC2Interrupt       _OC5Interrupt                                          */
/* _T2Interrupt        _OC6Interrupt                                          */
/* _T3Interrupt        _OC7Interrupt                                          */
/* _SPI1ErrInterrupt   _OC8Interrupt                                          */
/* _SPI1Interrupt      _DMA4Interrupt                                         */
/* _U1RXInterrupt      _T6Interrupt                                           */
/* _U1TXInterrupt      _T7Interrupt                                           */
/* _ADC1Interrupt      _SI2C2Interrupt                                        */
/* _DMA1Interrupt      _MI2C2Interrupt                                        */
/* _SI2C1Interrupt     _T8Interrupt                                           */
/* _MI2C1Interrupt     _T9Interrupt                                           */
/* _CNInterrupt        _INT3Interrupt                                         */
/* _INT1Interrupt      _INT4Interrupt                                         */
/* _ADC2Interrupt      _C2RxRdyInterrupt                                      */
/* _DMA2Interrupt      _C2Interrupt                                           */
/* _OC3Interrupt       _DCIErrInterrupt                                       */
/* _OC4Interrupt       _DCIInterrupt                                          */
/* _T4Interrupt        _DMA5Interrupt                                         */
/* _T5Interrupt        _U1ErrInterrupt                                        */
/* _INT2Interrupt      _U2ErrInterrupt                                        */
/* _U2RXInterrupt      _DMA6Interrupt                                         */
/* _U2TXInterrupt      _DMA7Interrupt                                         */
/* _SPI2ErrInterrupt   _C1TxReqInterrupt                                      */
/* _SPI2Interrupt      _C2TxReqInterrupt                                      */
/* _C1RxRdyInterrupt                                                          */
/*                                                                            */
/* dsPIC33E Primary Interrupt Vector Names:                                   */
/*                                                                            */
/* _INT0Interrupt     _IC4Interrupt      _U4TXInterrupt                       */
/* _IC1Interrupt      _IC5Interrupt      _SPI3ErrInterrupt                    */
/* _OC1Interrupt      _IC6Interrupt      _SPI3Interrupt                       */
/* _T1Interrupt       _OC5Interrupt      _OC9Interrupt                        */
/* _DMA0Interrupt     _OC6Interrupt      _IC9Interrupt                        */
/* _IC2Interrupt      _OC7Interrupt      _PWM1Interrupt                       */
/* _OC2Interrupt      _OC8Interrupt      _PWM2Interrupt                       */
/* _T2Interrupt       _PMPInterrupt      _PWM3Interrupt                       */
/* _T3Interrupt       _DMA4Interrupt     _PWM4Interrupt                       */
/* _SPI1ErrInterrupt  _T6Interrupt       _PWM5Interrupt                       */
/* _SPI1Interrupt     _T7Interrupt       _PWM6Interrupt                       */
/* _U1RXInterrupt     _SI2C2Interrupt    _PWM7Interrupt                       */
/* _U1TXInterrupt     _MI2C2Interrupt    _DMA8Interrupt                       */
/* _AD1Interrupt      _T8Interrupt       _DMA9Interrupt                       */
/* _DMA1Interrupt     _T9Interrupt       _DMA10Interrupt                      */
/* _NVMInterrupt      _INT3Interrupt     _DMA11Interrupt                      */
/* _SI2C1Interrupt    _INT4Interrupt     _SPI4ErrInterrupt                    */
/* _MI2C1Interrupt    _C2RxRdyInterrupt  _SPI4Interrupt                       */
/* _CM1Interrupt      _C2Interrupt       _OC10Interrupt                       */
/* _CNInterrupt       _QEI1Interrupt     _IC10Interrupt                       */
/* _INT1Interrupt     _DCIEInterrupt     _OC11Interrupt                       */
/* _AD2Interrupt      _DCIInterrupt      _IC11Interrupt                       */
/* _IC7Interrupt      _DMA5Interrupt     _OC12Interrupt                       */
/* _IC8Interrupt      _RTCCInterrupt     _IC12Interrupt                       */
/* _DMA2Interrupt     _U1ErrInterrupt    _DMA12Interrupt                      */
/* _OC3Interrupt      _U2ErrInterrupt    _DMA13Interrupt                      */
/* _OC4Interrupt      _CRCInterrupt      _DMA14Interrupt                      */
/* _T4Interrupt       _DMA6Interrupt     _OC13Interrupt                       */
/* _T5Interrupt       _DMA7Interrupt     _IC13Interrupt                       */
/* _INT2Interrupt     _C1TxReqInterrupt  _OC14Interrupt                       */
/* _U2RXInterrupt     _C2TxReqInterrupt  _IC14Interrupt                       */
/* _U2TXInterrupt     _QEI2Interrupt     _OC15Interrupt                       */
/* _SPI2ErrInterrupt  _U3ErrInterrupt    _IC15Interrupt                       */
/* _SPI2Interrupt     _U3RXInterrupt     _OC16Interrupt                       */
/* _C1RxRdyInterrupt  _U3TXInterrupt     _IC16Interrupt                       */
/* _C1Interrupt       _USB1Interrupt     _ICDInterrupt                        */
/* _DMA3Interrupt     _U4ErrInterrupt    _PWMSpEventMatchInterrupt            */
/* _IC3Interrupt      _U4RXInterrupt     _PWMSecSpEventMatchInterrupt         */
/*                                                                            */
/* For alternate interrupt vector naming, simply add 'Alt' between the prim.  */
/* interrupt vector name '_' and the first character of the primary interrupt */
/* vector name.  There is no Alternate Vector or 'AIVT' for the 33E family.   */
/*                                                                            */
/* For example, the vector name _ADC2Interrupt becomes _AltADC2Interrupt in   */
/* the alternate vector table.                                                */
/*                                                                            */
/* Example Syntax:                                                            */
/*                                                                            */
/* void __attribute__((interrupt,auto_psv)) <Vector Name>(void)               */
/* {                                                                          */
/*     <Clear Interrupt Flag>                                                 */
/* }                                                                          */
/*                                                                            */
/* For more comprehensive interrupt examples refer to the C30 (MPLAB C        */
/* Compiler for PIC24 MCUs and dsPIC DSCs) User Guide in the                  */
/* <C30 compiler instal directory>/doc directory for the latest compiler      */
/* release.  For XC16, refer to the MPLAB XC16 C Compiler User's Guide in the */
/* <XC16 compiler instal directory>/doc folder.                               */
/*                                                                            */