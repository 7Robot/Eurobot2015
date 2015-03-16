/*
 * Template dsPIC33F
 * Compiler : Microchip xC16
 * µC : 33FJ128MC804
 * Mars 2015
 *
 *    ______ _____      _           _
 *   |___  /| ___ \    | |         | |
 *      / / | |_/ /___ | |__   ___ | |_
 *     / /  |    // _ \| '_ \ / _ \| __|
 *    / /   | |\ \ (_) | |_) | (_) | |_
 *   /_/    |_| \_\___/|____/ \___/'\__|
 *			      7robot.fr
 */


/********Les pragmas on en mangerait********/
// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
#pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure segment may be written)
#pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
#pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)


// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)


// FICD
#pragma config ICS = PGD3               // Comm Channel Select (Communicate on PGC3/EMUC3 and PGD3/EMUD3)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

/********Headers********/
#include <xc.h>
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <uart.h>

#include "user.h"          /* User funct/params, such as InitApp              */
#include "qei.h"           /* QEI definitions for easier use                  */
#include <libpic30.h>
//#include "globals.h"
#include "ax12.h"
#include "lib_asserv/lib_asserv_default.h"
#include "lib_asserv/lib_asserv.h"
#include "motor.h"


int main(int argc, char** argv) {

    long i = 0;
    // test du portB
    TRISB = 0x0;

    while (1) // boucle principale
    {
        for(i=0;i<10000;i++) {}
        PORTB = 0xFF;
        for(i=0;i<10000;i++) {}
        PORTB = 0x00;
    }
}

