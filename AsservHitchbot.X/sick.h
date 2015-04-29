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

#define SICK_AVANT_GAUCHE   4 //AN7
#define SICK_AVANT_DROIT    5 //AN6
#define SICK_ARRIERE_GAUCHE 6 //AN8
#define SICK_ARRIERE_DROIT  7 //AN1

#define DEFAULT_THRESHOLD 100 // 300 ~> 16 cm
#define MARGIN_SICK 30

/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/

void InitSick();

#endif	/* SICK_H */

