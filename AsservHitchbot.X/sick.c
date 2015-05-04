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
#include <stdio.h>
#include <stdbool.h>       /* Includes true/false definition                  */

#include "sick.h"
#include "lib_asserv/lib_asserv.h"
#include <timer.h>

#include "user.h"

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

volatile int channel = 0;		// canal de conversion actuel

volatile uint16_t Value_Sick[NUMBER_OF_SICK] = {0};		// full of 0	// récupère la valeur de l'ADC
volatile uint16_t Old_Sector[NUMBER_OF_SICK] = {0};		// full of 0	// tout ou rien sur les seuils

volatile uint16_t Threshold[NUMBER_OF_SICK] = {DEFAULT_THRESHOLD};

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

void InitSick()
{
	
   //Configuration du convertisseur Analog to Digital (ADC) du dspic33f
   //Cf page 286 dspic33f Data Sheet

   //AD1CON1 Configuration
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

   
   channel = 0;
   //Choix des références de tensions
							// Choix du (+) de la mesure pour le channel CH0, commençant par le sick 1 
   AD1CHS0bits.CH0SA = AN_CH_SICK_ARRIERE_DROIT;	
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
    // OpenTimer5(T5_ON & T5_GATE_OFF & T5_PS_1_256 & T5_SOURCE_INT, 15625); from 2014
    OpenTimer5(T5_ON & T5_GATE_OFF & T5_PS_1_64 & T5_SOURCE_INT, 3125 ); // for 2015
	// FCY = 40Meg
	// prescaller à 64 et comparaison à 3125 => 40M / (64*3125) = 200 => 200 départ de comparaison / sec
	// avec 4 canaux, ça fait 50 detections / sec
	

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
    if(id == 255) {
        for (i=0;i<NUMBER_OF_SICK;i++){
            Threshold[i] = threshold;
        }
    } else if(id >= 0 && id < NUMBER_OF_SICK) {
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
    static uint16_t i_debug_sick = 0;

    Value_Sick[channel] = ADC1BUF0; 	// récupération valeur depuis ADC
	
    if(  (Value_Sick[channel] > (Threshold[channel] + MARGIN_SICK))  &&  (Old_Sector[channel] == 0)  ) {		// si on repasse au dela de seuil + fenetre, on repasse dans la zone "ext"
        Old_Sector[channel] = 1;
       // SendSick(channel);
    } else if(  (Value_Sick[channel] < (Threshold[channel] - MARGIN_SICK)) &&  (Old_Sector[channel] == 1)  ) {	  // si on repasse en deça de seuil - fenetre, on repasse dans la zone "int" = danger
        Old_Sector[channel] = 0;
        motion_free();
        //SendFreepath(channel);
    }
	
    if (i_debug_sick == 200) {
        #ifdef DEBUG_SICK
            printf ("\nSick 1 : %d\nSick 2 : %d\nSick 3 : %d\nSick 4 : %d\n", Value_Sick[0], Value_Sick[1], Value_Sick[2], Value_Sick[3]);
        #endif
        i_debug_sick = 0;
    } else {
        i_debug_sick ++;
    }

    switch(channel)     // Select next sensor
    {
        case 0:
            _CH0SA = AN_CH_SICK_ARRIERE_GAUCHE;		// sick 2
            break;
        case 1:
            _CH0SA = AN_CH_SICK_AVANT_DROIT;		// sick 3
            break;
        case 2:
            _CH0SA = AN_CH_SICK_AVANT_GAUCHE;		// sick 4
            break;
        case 3:
            _CH0SA = AN_CH_SICK_ARRIERE_DROIT;		// sick 1
            break;
    }

    channel = (channel+1) % NUMBER_OF_SICK;

    _AD1IF = 0;        //Clear the interrupt flag
 }
