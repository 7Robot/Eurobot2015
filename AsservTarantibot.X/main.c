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
 *                7robot.fr
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


#include <stdint.h>        // Includes uint16_t definition
#include <stdio.h>         // Includes sprintf
#include <stdbool.h>       // Includes true/false definition
#include <uart.h>
#include <math.h>
#include "user.h"          // User funct/params, such as InitApp
#include "qei.h"           // QEI definitions for easier use
#include <libpic30.h>
#include "ax12.h"
#include "lib_asserv/lib_asserv_default.h"
#include "lib_asserv/lib_asserv.h"

#include "motor.h"
#include "actions_ax12.h"

extern volatile int tics_d;
extern volatile int tics_g;
int tics_now_d=0;
int tics_now_g=0;
extern float Vcons_d;
extern float Vcons_g;


int temp=0;

int main(int argc, char** argv) {
    //float valf = 0, sens = 1;
    Init_All();

    for (temp=0;temp<5;temp++)
        __delay_ms(200);

    int state=0;
    char done_d=0;
    char done_g=0;

    init_ax12();

    while(1){
        ///////////////////////////// PREMIER ETAT /////////////////////////////
        if (state==0)
        {
            if (tics_d-tics_now_d<1000) Vcons_d=8;
            else
            {
                Vcons_d=0;
                done_d=1;
            }
            if (tics_g-tics_now_g<1000) Vcons_g=8;
            else
            {
                Vcons_g=0;
                done_g=1;
            }
            // Fin du premier état si le compte est bon à gauche et à droite
            if (done_d==1 && done_g==1)
            {
                state=1;
                done_d=0;
                done_g=0;
                tics_now_d=tics_d;
                tics_now_g=tics_g;
                __delay_ms(1000);
            }
        }
        //////////////////////////// DEUXIEME ETAT /////////////////////////////
        else if (state==1)
        {
            if (tics_d-tics_now_d<1000) Vcons_d=-8;
            else
            {
                Vcons_d=-0.01;
                done_d=1;
            }
            if (tics_g-tics_now_g<1000) Vcons_g=-8;
            else
            {
                Vcons_g=-0.01;
                done_g=1;
            }
            // Fin du deuxième état si le compte est bon à gauche et à droite
            if (done_d==1 && done_g==1)
            {
                state=2;
                done_d=0;
                done_g=0;
                tics_now_d=tics_d;
                tics_now_g=tics_g;
                __delay_ms(1000);
            }
        }
        //deploy();
        //lacher();
        //ranger();
        //__delay_ms(2000);
    }
}


