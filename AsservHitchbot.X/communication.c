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
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

char ReceivedStringFromPi[50] = {0};
int CharFromPiNumber = 0;

void AnalyzeCommandFromPi (void)
{
    // Receive first Byte
    char b = ReadUART1();

    // If byte is "$" symbol, the string can be valid
    if (b=='$')
    {
        CharFromPiNumber = 0;
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
    float ANGLE;
    Position MOVE;
	uint8_t val8;

	// MOVE
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

	// ANGL
    if(ReceivedStringFromPi[1]=='A' && ReceivedStringFromPi[2]=='N' && ReceivedStringFromPi[3]=='G' && ReceivedStringFromPi[4]=='L')
    {
        cursorPosition=6;

        for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=';';floatLength++); // Return the number of char taken by the float in the command line
        ReceivedStringFromPi[cursorPosition+floatLength] = 0;
        ANGLE = atof(&ReceivedStringFromPi[cursorPosition]);
        ReceivedStringFromPi[cursorPosition+floatLength] = ';';

        motion_angle(ANGLE);
    }



    // INIT
    if(ReceivedStringFromPi[1]=='I' && ReceivedStringFromPi[2]=='N' && ReceivedStringFromPi[3]=='I' && ReceivedStringFromPi[4]=='T')
    {
        Init_All(1);
    }

    // AXIN
    if(ReceivedStringFromPi[1]=='A' && ReceivedStringFromPi[2]=='X' && ReceivedStringFromPi[3]=='I' && ReceivedStringFromPi[4]=='N')
    {
        Init_ax12();
    }

    // FREE
    if(ReceivedStringFromPi[1]=='F' && ReceivedStringFromPi[2]=='R' && ReceivedStringFromPi[3]=='E' && ReceivedStringFromPi[4]=='E')
    {
        motion_free();
    }

    // CHAR
    if(ReceivedStringFromPi[1]=='C' && ReceivedStringFromPi[2]=='H' && ReceivedStringFromPi[3]=='A' && ReceivedStringFromPi[4]=='R')
    {
        charg_spot();
    }

    // CHAL
    if(ReceivedStringFromPi[1]=='C' && ReceivedStringFromPi[2]=='H' && ReceivedStringFromPi[3]=='A' && ReceivedStringFromPi[4]=='L')
    {
        charg_last_spot();
    }

    // RELE
    if(ReceivedStringFromPi[1]=='R' && ReceivedStringFromPi[2]=='E' && ReceivedStringFromPi[3]=='L' && ReceivedStringFromPi[4]=='E')
    {
        release();
    }

    // CLOSE
    if(ReceivedStringFromPi[1]=='C' && ReceivedStringFromPi[2]=='L' && ReceivedStringFromPi[3]=='O' && ReceivedStringFromPi[4]=='S')
    {
        close_claws();
    }

    // TEAM
    if(ReceivedStringFromPi[1]=='T' && ReceivedStringFromPi[2]=='E' && ReceivedStringFromPi[3]=='A' && ReceivedStringFromPi[4]=='M')
    {
        SendTeam(PIN_TEAM);
    }

    // SIK?			// demande status sick
    if(ReceivedStringFromPi[1]=='S' && ReceivedStringFromPi[2]=='I' && ReceivedStringFromPi[3]=='K' && ReceivedStringFromPi[4]=='?')
    {
        val8 = ReceivedStringFromPi[6] -48; // 48 = 0 en ascii
        if (val8 >= NUMBER_OF_SICK) {
                val8 = 0;
        }
        __delay_ms(50);
        SendSick_Status(val8);
        __delay_ms(50);
    }

    // DBSI			// start/stop debug sick
    if(ReceivedStringFromPi[1]=='D' && ReceivedStringFromPi[2]=='B' && ReceivedStringFromPi[3]=='S' && ReceivedStringFromPi[4]=='I')
    {
        Start_Stop_Debug_Sick();
    }

    // ULS?			// demande status sick
    if(ReceivedStringFromPi[1]=='U' && ReceivedStringFromPi[2]=='L' && ReceivedStringFromPi[3]=='S' && ReceivedStringFromPi[4]=='?')
    {
        SendUltrason_Status();
    }

    // DBUS			// start/stop debug ultrason
    if(ReceivedStringFromPi[1]=='D' && ReceivedStringFromPi[2]=='B' && ReceivedStringFromPi[3]=='U' && ReceivedStringFromPi[4]=='S')
    {
        Start_Stop_Debug_Ultrason();
    }



}

void SendDone(void)
{
    __delay_ms(50);
    printf("$DONE;");
    __delay_ms(50);
}

void SendStart(void)
{
    __delay_ms(50);
    printf("$STRT;");
    __delay_ms(50);
}

void SendFailAX12(void)
{
    __delay_ms(50);
    printf("$FAAX;");
    __delay_ms(50);
}

void DetectSick(int channel)
{
   // __delay_ms(50);
    switch(channel){
        case 0 : printf("$DSI0;");  break;
        case 1 : printf("$DSI1;");  break;
        case 2 : printf("$DSI2;");  break;
        case 3 : printf("$DSI3;");  break;
    }
   // __delay_ms(50);
}

void ReleaseSick (int channel)
{
    //__delay_ms(50);
	switch(channel){
        case 0 : printf("$RSI0;");  break;
        case 1 : printf("$RSI1;");  break;
        case 2 : printf("$RSI2;");  break;
        case 3 : printf("$RSI3;");  break;
    }
    //__delay_ms(50);
}

void SendSick_Status(int val8)
{
    __delay_ms(50);
    printf("$SICK,%d,%d,%d;", val8, Get_Sick(val8), Get_Sick_Sector(val8) );
	__delay_ms(50);
}

void DetectUltrason(void)
{
    printf("$DULS;");
}

void ReleaseUltrason(void)
{
    printf("$RULS;");
}

void SendUltrason_Status(void)
{
    __delay_ms(50);
    printf("$SULS,%d,%d,%d;", Sector_Ultrason, Mesure_Distance_Ultrason, Mesure_Timer_Ultrason);
    __delay_ms(50);
}

void SendTeam (int team)
{
    __delay_ms(50);
    switch(team) {
        case 0 : printf("$YELL;");  break;
        case 1 : printf("$GREE;");  break;
    }
    __delay_ms(50);
}

