/*
 * Template dsPIC33F
 * Compiler : Microchip xC16
 * �C : 33FJ128MC804
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
#include <stdio.h>
#include <stdlib.h>
#include "lib_asserv/private/motion.h"

char ReceivedStringFromPi[50] = {0};
int CharFromPiNumber = 0;

void AnalyzeCommandFromPi (void)
{
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
        SelectActionFromPi();
    }
}

void SelectActionFromPi()
{
    int cursorPosition, floatLength;
    Position MOVE;

    if(ReceivedStringFromPi[1]=='M' && ReceivedStringFromPi[2]=='O' && ReceivedStringFromPi[3]=='V' && ReceivedStringFromPi[4]=='E')
    {
        cursorPosition=6;
        for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=',';floatLength++); // Return the number of char taken by the float in the command line
        ReceivedStringFromPi[cursorPosition+floatLength] = 0;
        MOVE.x = atof(&ReceivedStringFromPi[cursorPosition]);
        ReceivedStringFromPi[cursorPosition+floatLength] = ',';

        cursorPosition+=floatLength+1;
        for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=',';floatLength++); // Return the number of char taken by the float in the command line
        ReceivedStringFromPi[cursorPosition+floatLength] = 0;
        MOVE.y = atof(&ReceivedStringFromPi[cursorPosition]);
        ReceivedStringFromPi[cursorPosition+floatLength] = ',';

        cursorPosition+=floatLength+1;
        for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=';';floatLength++); // Return the number of char taken by the float in the command line
        ReceivedStringFromPi[cursorPosition+floatLength] = 0;
        MOVE.t = atof(&ReceivedStringFromPi[cursorPosition]);
        ReceivedStringFromPi[cursorPosition+floatLength] = ';';
        
        motion_pos(MOVE);
    }
}
