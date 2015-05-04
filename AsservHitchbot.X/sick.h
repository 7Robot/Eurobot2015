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

#define AN_CH_SICK_ARRIERE_DROIT  7 //AN7		=> // an_sick 1
#define AN_CH_SICK_ARRIERE_GAUCHE 6 //AN6		=> // an_sick 2
#define AN_CH_SICK_AVANT_DROIT    5 //AN5		=> // an_sick 3
#define AN_CH_SICK_AVANT_GAUCHE   4 //AN4		=> // an_sick 4


#define DEFAULT_THRESHOLD 100 // 300 ~> 16 cm
#define MARGIN_SICK 30		// en réalité, plutot un triger de schmitt

/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/

void InitSick();

#endif	/* SICK_H */

