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



/********Headers********/
#include <xc.h>
/******************************************************************************/
/* Configuration                                                             */
/******************************************************************************/

// Select Oscillator and switching.
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
// Select clock.
_FOSC(POSCMD_NONE & OSCIOFNC_ON & IOL1WAY_ON & FCKSM_CSDCMD);
// Watchdog Timer.
_FWDT(FWDTEN_OFF);
// Select debug channel.
_FICD(ICS_PGD3 & JTAGEN_OFF);

_FPOR(PWMPIN_ON);


#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdio.h>
#include <stdbool.h>       /* Includes true/false definition                  */
#include <uart.h>
#include <math.h>
#include "user.h"          /* User funct/params, such as InitApp              */
#include "qei.h"           /* QEI definitions for easier use                  */
#include <libpic30.h>
#include "ax12.h"
#include "lib_asserv/lib_asserv_default.h"
#include "lib_asserv/lib_asserv.h"
#include "motor.h"
#include "actions_ax12.h"


int main(int argc, char** argv) {
    //float valf = 0, sens = 1;
    Init_All();

////test de vitesse
//    Speed test ;
//    test.v=0.1;
//    test.vt = 0;
//    motion_speed(test);

    while (1) // boucle principale
    {

//   Position Coord;
//    Coord.x = 0;
//    Coord.y = 0;
//    Coord.t = 0;
//
//    set_position(Coord);
//    __delay_ms(50);
//
//
//    init_ax12();
//
//    Coord.x = 1;
//    motion_pos(Coord);
//    __delay_ms(2000);
//    charg_gobelet();
//    __delay_ms(50);
//    Coord.x = 0;
//    motion_pos(Coord);
//    __delay_ms(2000);
    }
}


