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
    float valf;
    Position MOVE;
    uint8_t val8;
    char valc;

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
        Add_Action_AX12(AX12_INIT_AX12);
    }

    // FREE
    if(ReceivedStringFromPi[1]=='F' && ReceivedStringFromPi[2]=='R' && ReceivedStringFromPi[3]=='E' && ReceivedStringFromPi[4]=='E')
    {
        motion_free();
    }

    // CHAR
    if(ReceivedStringFromPi[1]=='C' && ReceivedStringFromPi[2]=='H' && ReceivedStringFromPi[3]=='A' && ReceivedStringFromPi[4]=='R')
    {
        Add_Action_AX12(AX12_CHARG_SPOT);
    }

    // CHAL
    if(ReceivedStringFromPi[1]=='C' && ReceivedStringFromPi[2]=='H' && ReceivedStringFromPi[3]=='A' && ReceivedStringFromPi[4]=='L')
    {
        Add_Action_AX12(AX12_CHARG_LAST_SPOT);
    }

    // RELE
    if(ReceivedStringFromPi[1]=='R' && ReceivedStringFromPi[2]=='E' && ReceivedStringFromPi[3]=='L' && ReceivedStringFromPi[4]=='E')
    {
        Add_Action_AX12(AX12_RELEASE);
    }

    // CLOSE
    if(ReceivedStringFromPi[1]=='C' && ReceivedStringFromPi[2]=='L' && ReceivedStringFromPi[3]=='O' && ReceivedStringFromPi[4]=='S')
    {
        Add_Action_AX12(AX12_CLOSE_CLAWS);
    }
        
    if(ReceivedStringFromPi[1]=='O' && ReceivedStringFromPi[2]=='P' && ReceivedStringFromPi[3]=='E' && ReceivedStringFromPi[4]=='S')
    {
        Add_Action_AX12(AX12_OPEN_CLAWS);
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
    
    // ENSI         // active ou pas le motion_free des sicks  à l'unitée
    if(ReceivedStringFromPi[1]=='E' && ReceivedStringFromPi[2]=='N' && ReceivedStringFromPi[3]=='S' && ReceivedStringFromPi[4]=='I')
    {
        // l'utilisateur a juste droit à de 0 à F
        valc = ReceivedStringFromPi[6];
        if (valc >= '0' && valc <= '9') {
            valc -= '0';
        } else if (valc >= 'A' && valc <= 'F') {
            valc -= 'A';
        } else {
            valc = 0x0F;
        }
        Choose_Enabled_Sicks(valc);
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

    // ENUS         // active ou pas le motion_free de l'ultrason
    if(ReceivedStringFromPi[1]=='E' && ReceivedStringFromPi[2]=='N' && ReceivedStringFromPi[3]=='U' && ReceivedStringFromPi[4]=='S')
    {
        Enable_Ultrason(ReceivedStringFromPi[6] != '0');
    }

    // VBAT			// récupère la tension baterie
    if(ReceivedStringFromPi[1]=='V' && ReceivedStringFromPi[2]=='B' && ReceivedStringFromPi[3]=='A' && ReceivedStringFromPi[4]=='T')
    {
        __delay_ms(50);
        printf("$VBAT,%d;", V_Bat);
        __delay_ms(50);
    }

	// CLRO
    if(ReceivedStringFromPi[1]=='C' && ReceivedStringFromPi[2]=='L' && ReceivedStringFromPi[3]=='R' && ReceivedStringFromPi[4]=='O')
    {
        Add_Action_AX12(AX12_OPEN_CLAPR);
    }

	// CLRC
    if(ReceivedStringFromPi[1]=='C' && ReceivedStringFromPi[2]=='L' && ReceivedStringFromPi[3]=='R' && ReceivedStringFromPi[4]=='C')
    {
        Add_Action_AX12(AX12_CLOSE_CLAPR);
    }

	// CLLO
    if(ReceivedStringFromPi[1]=='C' && ReceivedStringFromPi[2]=='L' && ReceivedStringFromPi[3]=='L' && ReceivedStringFromPi[4]=='O')
    {
        Add_Action_AX12(AX12_OPEN_CLAPL);
    }

	// ouvrir popcorn droit
    if(ReceivedStringFromPi[1]=='P' && ReceivedStringFromPi[2]=='O' && ReceivedStringFromPi[3]=='O' && ReceivedStringFromPi[4]=='R')
    {
        Add_Action_AX12(AX12_OPEN_POPCORN_D);
    }

    if(ReceivedStringFromPi[1]=='P' && ReceivedStringFromPi[2]=='O' && ReceivedStringFromPi[3]=='C' && ReceivedStringFromPi[4]=='R')
    {
        Add_Action_AX12(AX12_CLOSE_POPCORN_D);
    }
    	// ouvrir popcorn gauche
    if(ReceivedStringFromPi[1]=='P' && ReceivedStringFromPi[2]=='O' && ReceivedStringFromPi[3]=='O' && ReceivedStringFromPi[4]=='L')
    {
        Add_Action_AX12(AX12_OPEN_POPCORN_G);
    }

    if(ReceivedStringFromPi[1]=='P' && ReceivedStringFromPi[2]=='O' && ReceivedStringFromPi[3]=='C' && ReceivedStringFromPi[4]=='L')
    {
        Add_Action_AX12(AX12_OPEN_POPCORN_G);
    }

    // CLTB
    if(ReceivedStringFromPi[1]=='C' && ReceivedStringFromPi[2]=='L' && ReceivedStringFromPi[3]=='T' && ReceivedStringFromPi[4]=='B')
    {
        Add_Action_AX12(AX12_CLOSE_TUB);
    }

    // VMAX     choisi une vitesse max
    if(ReceivedStringFromPi[1]=='V' && ReceivedStringFromPi[2]=='M' && ReceivedStringFromPi[3]=='A' && ReceivedStringFromPi[4]=='X')
    {
        cursorPosition=6; 
        for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=';';floatLength++); // Return the number of char taken by the float in the command line
        ReceivedStringFromPi[cursorPosition+floatLength] = 0;
        valf = atof(&ReceivedStringFromPi[cursorPosition]);
        ReceivedStringFromPi[cursorPosition+floatLength] = ';';
        set_Constraint_vitesse_max(valf);
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
    __delay_ms(2);
    switch(channel){
        case 0 : printf("$DSI0;");  break;
        case 1 : printf("$DSI1;");  break;
        case 2 : printf("$DSI2;");  break;
        case 3 : printf("$DSI3;");  break;
    }
   __delay_ms(2);
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

