/*
 * Template dsPIC33F
 * Compiler : Microchip xC16
 * µC : 33FJ128MC804
 * Avril 2015
 *
 *    ______ _____      _           _
 *   |___  /| ___ \    | |         | |
 *      / / | |_/ /___ | |__   ___ | |_
 *     / /  |    // _ \| '_ \ / _ \| __|
 *    / /   | |\ \ (_) | |_) | (_) | |_
 *   /_/    |_| \_\___/|____/ \___/'\__|
 *			      7robot.fr
 */

#include <uart.h>
#include "communication.h"

char ReceivedStringFromPi[50] = {0};
int CharFromPiNumber = 0;

void AnalyzeCommandFromPi (void)
{
    // while(DataRdyUART1());
    // Receive first Byte
    char b = ReadUART1();

    // If byte is "$" symbol, the string can be valid
    if (b=='$')
    {
        ReceivedStringFromPi[CharFromPiNumber] = b;
        CharFromPiNumber++;
    }
    // Here we are collecting all the char from the frame
    else if (b!=';' && CharFromPiNumber > 0)
    {
        ReceivedStringFromPi[CharFromPiNumber] = b;
        CharFromPiNumber++;
    }
    // End of the frame, the symbol is a ;
    else if (CharFromPiNumber > 0)
    {
        ReceivedStringFromPi[CharFromPiNumber] = b;
        /*** Full frame received and available in ReceivedStringFromPi ***/
    }
}

