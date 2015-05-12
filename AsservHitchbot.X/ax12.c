/*
* Template dsPIC33F
* Compiler : Microchip xC16
* ÂµC : 33FJ64MC804
* Juillet 2012
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*                 7robot.fr
*/

#include <uart.h>
#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>
#include <delay.h>

#include "main.h"

/******************************************************************************
 * Global Variables
 ******************************************************************************/
byte checksumAX;
volatile int posAX = -5;



volatile int Delay_TimeOut_AX12 = 0;

/*
 * Public global variables, which have to be declared volatile.
 */
volatile int responseReadyAX = 0;
responseAXtype responseAX;

/******************************************************************************
 * Wiring dependent functions, that you should customize
 ******************************************************************************/

// du coup, le bit IOLOCK est à 0 au reset du pic,
// donc on va pas y toucher, ça permet de tout faire marcher facile....

void SetTX() {
    //__builtin_write_OSCCONL(0x46);
    //__builtin_write_OSCCONL(0x57);
    //__builtin_write_OSCCONL(OSCCON & 0xBF);
    _U2RXR = 31;                        // disable RX
    PIN_REMAPABLE_AX12_OUT = 0b00101;   // RP10 = U2TX (p.167)      TX => RP10
    //__builtin_write_OSCCONL(OSCCON | 0x40);
}

void SetRX() {
    //__builtin_write_OSCCONL(0x46);
    //__builtin_write_OSCCONL(0x57);
    //__builtin_write_OSCCONL(OSCCON & 0xBF);     // IOLOCK = 0
    _U2RXR = PIN_REMAPABLE_AX12_IN;     // RP10 = U2RX (p.165)      RX <= RP10
    PIN_REMAPABLE_AX12_OUT = 0;         // disable TX
    // __builtin_write_OSCCONL(OSCCON | 0x40);

}

/******************************************************************************
 * Functions to read and write command and return packets
 ******************************************************************************/

void PushUART(byte b) {
    while (U2STAbits.UTXBF); // UART2 TX Buffer Full
    WriteUART2(b);
    checksumAX += b;
}

/*
 * Write the first bytes of a command packet, assuming a <len> parameters will
 * follow.
 */
void PushHeaderAX(byte id, byte len, byte inst) {
    SetTX();

    PushUART(0xFF);
    PushUART(0xFF);

    checksumAX = 0; // The first two bytes don't count.
    PushUART(id);
    PushUART(len + 2); // Bytes to go : instruction + buffer (len) + checksum.
    PushUART(inst);
}

/* Write a buffer of given length to the body of a command packet. */
void PushBufferAX(byte len, byte* buf) {
    byte i;
    for (i = 0; i < len; i++) {
        PushUART(buf[i]);
    }
}

/* Finish a command packet by sending the checksum. */
void PushFooterAX() {
    PushUART(~checksumAX);
    while (BusyUART2()); // UART1 Transmit Shift Register Empty
    SetRX();
}

/**/
void InterruptAX() {
    while(DataRdyUART2()) {
        byte b = ReadUART2();

        if(posAX == -5 && b == 0xFF)
            posAX = -4;
        else if(posAX == -4 && b == 0xFF) {
            posAX = -3;
            checksumAX = 0;
            responseAX.len = 1;
        }
        else if(posAX == -3) {
            posAX = -2;
            responseAX.id = b;
        }
        else if(posAX == -2 && b < 2 + 4 /*taille de ax.parameters*/) {
            posAX = -1;
            checksumAX = responseAX.id + b;
            responseAX.len = b - 2;
        }
        else if(posAX == -1) {
            posAX = 0;
            responseAX.error = *((errorAX*)&b);
        }
        else if(0 <= posAX && posAX < responseAX.len) {
            ((byte*)&responseAX.params)[posAX++] = b;
            checksumAX += b;
        }
        else if(posAX == responseAX.len && (b & checksumAX) == 0) {
            responseReadyAX = 1;
            posAX = -5;
        }
        else
            posAX = -5; // Erreur.
    }
}


/******************************************************************************
 * Instructions Implementation
 ******************************************************************************/

void PingAX(byte id) {
    PushHeaderAX(id, 2, AX_INST_PING);
    PushFooterAX();
}

void ReadAX(byte id, byte address, byte len) {
    PushHeaderAX(id, 2, AX_INST_READ_DATA);
    PushUART(address);
    PushUART(len);
    PushFooterAX();
}

void WriteAX(byte id, byte address, byte len, byte* buf) {
    PushHeaderAX(id, 1 + len, AX_INST_WRITE_DATA);
    PushUART(address);
    PushBufferAX(len, buf);
    PushFooterAX();
}

void RegWriteAX(byte id, byte address, byte len, byte* buf) {
    PushHeaderAX(id, 1 + len, AX_INST_REG_WRITE);
    PushUART(address);
    PushBufferAX(len, buf);
    PushFooterAX();
}

void ActionAX(byte id) {
    PushHeaderAX(id, 0, AX_INST_ACTION);
    PushFooterAX();
}

void ResetAX(byte id) {
    PushHeaderAX(id, 0, AX_INST_RESET);
    PushFooterAX();
}


/******************************************************************************
 * Convenience Functions
 ******************************************************************************/

byte RegisterLenAX(byte address) {
    switch (address) {
        case  2: case  3: case  4: case  5: case 11: case 12: case 13: case 16:
        case 17: case 18: case 19: case 24: case 25: case 26: case 27: case 28:
        case 29: case 42: case 43: case 44: case 46: case 47:
            return 1;
            break;
        case  0: case  6: case  8: case 14: case 20: case 22: case 30: case 32:
        case 34: case 36: case 38: case 40: case 48:
            return 2;
            break;
    }
    return 0; // Unexpected.
}

// old version :
/* Write a value to a registry, guessing its width. 
void PutAX(byte id, byte address, int value) {
    responseReadyAX = 0;
    WriteAX(id, address, RegisterLenAX(address), (byte*)&value);
}
 * */

/* Read a value from a registry, guessing its width. */
void GetAX(byte id, byte address) {
    responseReadyAX = 0;
    ReadAX(id, address, RegisterLenAX(address));
}

char PutAX(byte id, byte address, int value) {
#ifdef DOUBLE_COMMANDE_AX12
    WriteAX(id, address, RegisterLenAX(address), (byte*)&value);
    __delay_ms(7);
    WriteAX(id, address, RegisterLenAX(address), (byte*)&value);
    return 0;
#else
#ifdef TEST_RECEPTION_AX12
    char i = 0;
    char OK = 0;
    while (i < 10 && !OK) {
        OK = PutAX_Check(id, address, value);
        i++;
    }
    return (OK == 0);
#else
    WriteAX(id, address, RegisterLenAX(address), (byte*)&value);
    return 0;
#endif
#endif


}


// Write a value to a registry, guessing its width.
// écoute ensuite la réponse, timeout à 10ms
// si réponse pas bonne, on retente
char PutAX_Check(byte id, byte address, int value) {
    char Reponse_Ok = 1;
    
    responseReadyAX = 0;    // reset la reception
    posAX = -5;             // reset BIS

    WriteAX(id, address, RegisterLenAX(address), (byte*)&value );
    Delay_TimeOut_AX12 = 10;

    // tant que le timer 10ms a pas déclenché, et que l'on a pas reçu la réponse de l'AX
    while (Delay_TimeOut_AX12 && !responseReadyAX);

    if (responseReadyAX) {      // si on a eu une réponse, on l'analyse
        if (responseAX.id != id) {
            Reponse_Ok = 0;
        }else if (    responseAX.error.input_voltage  || responseAX.error.angle_limit     ||
                responseAX.error.overheating    || responseAX.error.range           ||
                responseAX.error.cheksum        || responseAX.error.overload        ||
                responseAX.error.instruction        ) {
            Reponse_Ok = 0;
        }
    } else {    // si pas de réponse
        Reponse_Ok = 0;
    }

    return Reponse_Ok;
}

