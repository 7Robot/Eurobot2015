/*
* Sick
* Compiler : Microchip xC16
* �C : 33FJ64MC804
* Mai 2014
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*			      7robot.fr
*/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC33E__)
    	#include <p33Exxxx.h>
    #elif defined(__dsPIC33F__)
    	#include <p33Fxxxx.h>
    #endif
#endif

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "sick.h"
#include <timer.h>

#include "user.h"

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

volatile int channel = 0;
volatile uint16_t Sector[NUMBER_OF_SICK] = {0,0,0,0};
volatile uint16_t Old_Sector[NUMBER_OF_SICK] = {0,0,0,0};

volatile uint16_t Threshold[NUMBER_OF_SICK] = {DEFAULT_THRESHOLD, DEFAULT_THRESHOLD, DEFAULT_THRESHOLD, DEFAULT_THRESHOLD};

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

void InitSick()
{
   //Configuration du convertisseur Analog to Digital (ADC) du dspic33f
   //Cf page 286 dspic33f Data Sheet

   //AD1CON1 Confugration
   AD1CON1bits.ADON = 0;    //Eteindre A/D converter pour la configuration
   AD1CON1bits.FORM = 0;    //Configure le format de la sortie de l'ADC ( 3=signed float, 2=unsigned float, 1=signed integer, 0=unsigned integer
   AD1CON1bits.SSRC = 4;    //Config de l'échantillonnage : Timer5
   AD1CON1bits.SIMSAM = 0;  //Simultaneously Sample CH0
   AD1CON1bits.ASAM = 1;    //Début d'échantillonnage (1=tout de suite  0=dès que AD1CON1bits.SAMP est activé)
   AD1CON1bits.AD12B = 0;   //Choix du type de converter (10 ou 12 bits) 0 = 10 bits , 1 = 12bits

   //AD1CON2 Configuration
   AD1CON2bits.ALTS = 0;     //Always sampling on channel A
   AD1CON2bits.CHPS = 0;    //Select CH0

   //AD1CON3 Configuration
   AD1CON3bits.ADRC = 1;        //Choix du type de clock interne (=1) ou externe (=0)

   //Choix des références de tensions
   AD1CHS0bits.CH0SA = 4;	// Choix du (+) de la mesure pour le channel CH0 (0 = AN0) par défault
   AD1CHS0bits.CH0NA = 0;	// Choix du (-) de la mesure pour le channel CH0 (0 = Masse interne pic)

   //Configuration des pins analogiques
   //AD1PCFGL = 0xFFFF;   //Met tous les ports AN en Digital Input
   //AD1PCFGLbits.PCFG0 = 0;
   //AD1PCFGLbits.PCFG2 = 0;
   //AD1PCFGLbits.PCFG3 = 0;
   //AD1PCFGLbits.PCFG4 = 0;
   //AD1PCFGLbits.PCFG5 = 0;
   /* COM A ENLEVER SUR DSPIC AVEC 8 PINS ANALOGIQUES */
   AD1PCFGLbits.PCFG4 = 0;
   AD1PCFGLbits.PCFG5 = 0;
   AD1PCFGLbits.PCFG6 = 0;
   AD1PCFGLbits.PCFG7 = 0;

   //Configuration du Timer 5, pour l'ADC
    OpenTimer5(T5_ON & T5_GATE_OFF & T5_PS_1_256 & T5_SOURCE_INT, 15625);

   //Configuration des interuption
   IFS0bits.AD1IF = 0;      //Mise à 0 du flag d'interrupt de ADC1
   IEC0bits.AD1IE = 1;      //Enable les interruptions d'ADC1
   IPC3bits.AD1IP = 2;      //Et les priorités (ici prio = 2)
   AD1CON1bits.SAMP = 0;
   AD1CON1bits.ADON = 1;    // Turn on the A/D converter
}

void OnSickThreshold(unsigned char id, unsigned int threshold)
{
    int i=0;
    if(id == 255)
    {
        for (i=0;i<NUMBER_OF_SICK;i++){
            Threshold[i] = threshold;
        }
    }
    else if(id >= 0 && id < NUMBER_OF_SICK)
    {
        Threshold[id] = threshold;
    }
}

void OnAskSick(unsigned char id){
   // SendSickState(id,Old_Sector[id]);
}

/******************************************************************************/
/* Interrupt                                                                  */
/******************************************************************************/

void __attribute__ ((interrupt, auto_psv)) _ADC1Interrupt(void)
 {

    Sector[channel] = ADC1BUF0;
    if(Sector[channel] > Threshold[channel] + MARGIN_SICK && Old_Sector[channel] == 0)
    {
        Old_Sector[channel] = 1;
       // SendSick(channel);
    }
    else if(Sector[channel] < Threshold[channel] - MARGIN_SICK && Old_Sector[channel] == 1)
    {
        Old_Sector[channel] = 0;
        //SendFreepath(channel);
    }

    switch(channel)     // Select next sensor
    {
        case 0:
            _CH0SA = SICK_AVANT_DROIT;
            break;
        case 1:
            _CH0SA = SICK_AVANT_GAUCHE;
            break;
        case 2:
            _CH0SA = SICK_ARRIERE_GAUCHE;
            break;
        case 3:
            _CH0SA = SICK_ARRIERE_DROIT;
            break;
    }

    channel = (channel+1)%NUMBER_OF_SICK;

    _AD1IF = 0;        //Clear the interrupt flag
 }
