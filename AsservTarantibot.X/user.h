#ifndef _USER_H_
#define _USER_H_

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
#define led _LATA2
#define BOUTON_COULEUR _RC3
#define MOT_SENSOR_PIN_L _RC8
#define MOT_SENSOR_PIN_R _RC9
#define PIN_LAISSE _RC4

/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        80000000UL
#define FCY             SYS_FREQ/2

///////////////////////// Le bon baudrate est de 57600 /////////////////////////
//#define BAUDRATEAX12 1000000
//#define BAUDRATEAX12 500000
//#define BAUDRATEAX12 400000
//#define BAUDRATEAX12 250000
//#define BAUDRATEAX12 200000
//#define BAUDRATEAX12 115200
#define BAUDRATEAX12 57600
//#define BAUDRATEAX12 38400
//#define BAUDRATEAX12 19200
//#define BAUDRATEAX12 9600

#define BRGVALAX12 ((FCY / BAUDRATEAX12 / 16) - 1)



/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
void InitTimers();
void Init_CN(void);
// initialize all things
void Init_All();

#endif // _USER_H_
