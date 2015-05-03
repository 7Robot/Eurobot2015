#include <xc.h>



#include <stdint.h>          /* For uint16_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include <timer.h>

//#include "tests.h"
//#include "atp-asserv.h"
//#include "atp.h"
//#include "sick.h"

#include "main.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

void ConfigureOscillator(void)
{
    // Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBDbits.PLLDIV = 150;        // M=152
    CLKDIVbits.PLLPRE  = 5;         // N1=7
    CLKDIVbits.PLLPOST = 0;         // N2=2
    /* Fosc = M/(N1.N2)*Fin
     * Fin : 7.37MHz (quartz interne)
     * Fosc à 80 MHZ (ne doit pas dépasser 80 MHZ)
     * la solution la plus proche est 152*7.37/(7*2) = 80.017
     * attention, cela entraine donc une FCY et une FPériphériques à 40 MHZ
     */
    while (!OSCCONbits.LOCK);       // attente que la PLL soit lockée sur se nouvelle configuration.
}


// initialize all things
void Init_All(){
    /* Configure the oscillator for the device */
    ConfigureOscillator();
    /* Initialize IO ports and peripherals */
    InitTimers();
    __delay_ms(500);
    Init_PWM();
    Init_QEI();
    Init_ax12();
    //InitSick();
    motion_init(); // start asserv
    //Init_CN();

}

/*
void writeStringToUART (const char *msg)
{
    while(*msg)    {
        WriteUART1(*msg++);
    }
}
*/