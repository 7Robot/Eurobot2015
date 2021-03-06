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

#ifndef SICK_H
#define	SICK_H

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define NUMBER_OF_SICK 4
#define NUMBER_OF_POINTS_MOY_SICK 16

#define AN_CH_SICK_ARRIERE_DROIT  7 //AN7		=> // an_sick 1
#define AN_CH_SICK_ARRIERE_GAUCHE 6 //AN6		=> // an_sick 2
#define AN_CH_SICK_AVANT_DROIT    5 //AN5		=> // an_sick 3
#define AN_CH_SICK_AVANT_GAUCHE   4 //AN4		=> // an_sick 4
#define AN_CH_V_BAT               0

#define SICK_AV_DROIT   2   //sick 3
#define SICK_AV_GAUCHE  3   //sick 4
#define SICK_AR_DROIT   0   //sick 1
#define SICK_AR_GAUCHE  1   //sick 2



#define DEFAULT_THRESHOLD 420 // 300 ~> 16 cm
#define MARGIN_SICK 20		// en réalité, plutot un triger de schmitt
#define SICK_LIMIT_MIN 30	// limite minimum qui fait passer un sick en off


#define TIMER_FOR_VBAT  399    //  400 / sec, donc 2000 donne toutes les 5 secondes
#define NUMBER_MEAS_VBAT 8


//#define DEBUG_SICK

/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/

void InitSick_VBat();

uint16_t Get_Sick(uint8_t Sick_Voulu);
uint16_t Get_Sick_Sector (uint8_t Sick_Voulu);

void Start_Stop_Debug_Sick(void);

extern volatile uint16_t V_Bat;

void Choose_Enabled_Sicks(char Sicks_En);

#endif	/* SICK_H */

