#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <uart.h>
#include <delay.h>

#include "main.h"

#define maxtork_claw 500
#define maxspeed_claw 500
#define delay_ax 30

/******************************************************************************/
/*************************** Arm Specification ********************************/
/******************************************************************************/


/******************************************************************************/
/****************************** Init Position *********************************/
/******************************************************************************/

void Init_ax12() {

    PutAX(rabd, AX_TORQUE_LIMIT, maxtork_claw);
    __delay_ms(delay_ax);
    PutAX(rabg, AX_TORQUE_LIMIT, maxtork_claw);
    __delay_ms(delay_ax);
    PutAX(pince, AX_TORQUE_LIMIT, 500);
    __delay_ms(delay_ax);
    PutAX(asc, AX_TORQUE_LIMIT, 900);
    __delay_ms(delay_ax);
    PutAX(tub, AX_TORQUE_LIMIT, 600);
    __delay_ms(delay_ax);
    PutAX(clap, AX_TORQUE_LIMIT, maxtork_claw);
    __delay_ms(delay_ax);
    PutAX(popcorn, AX_TORQUE_LIMIT, maxtork_claw);
    __delay_ms(delay_ax);


    PutAX(rabd, AX_MOVING_SPEED, maxspeed_claw);
    __delay_ms(delay_ax);
    PutAX(rabg, AX_MOVING_SPEED, maxspeed_claw);
    __delay_ms(delay_ax);
    PutAX(pince, AX_MOVING_SPEED, 400);
    __delay_ms(delay_ax);
    PutAX(asc, AX_MOVING_SPEED, 600);
    __delay_ms(delay_ax);
    PutAX(tub, AX_MOVING_SPEED, 450);
    __delay_ms(delay_ax);
    PutAX(clap, AX_MOVING_SPEED, maxspeed_claw);
    __delay_ms(delay_ax);
    PutAX(popcorn, AX_MOVING_SPEED, maxspeed_claw);
    __delay_ms(delay_ax);


    PutAX(asc, AX_GOAL_POSITION, 320);
    __delay_ms(500);
    PutAX(rabd,AX_GOAL_POSITION,200);
    __delay_ms(700);
    PutAX(rabg,AX_GOAL_POSITION,750);
    __delay_ms(700);
    //PutAX(rabd, AX_GOAL_POSITION, 620);
    //__delay_ms(500);
    //PutAX(rabg, AX_GOAL_POSITION, 390);
    //__delay_ms(500);
    PutAX(pince, AX_GOAL_POSITION, 260);
    __delay_ms(40);
    PutAX(tub, AX_GOAL_POSITION, 350);
    __delay_ms(40);
    PutAX(clap, AX_GOAL_POSITION, 512);
    __delay_ms(40);
    PutAX(popcorn, AX_GOAL_POSITION, 612);
    __delay_ms(40);

}

void charg_spot(void)
{
//int k;
    PutAX(rabd,AX_GOAL_POSITION,300); //rabat la piece 700
    __delay_ms(700);
//        while (  != 330) GetAX(rab,AX_PRESENT_POSITION); 200
    PutAX(rabd,AX_GOAL_POSITION,620); //reouvre
    __delay_ms(700);
    PutAX(rabg,AX_GOAL_POSITION,850); //rabat la piece 700
    __delay_ms(700);
//        while (  != 330) GetAX(rab,AX_PRESENT_POSITION); 200
    PutAX(rabg,AX_GOAL_POSITION,390); //reouvre
    __delay_ms(50);

    if (PORTAbits.RA9 == 1) {


//        while (  != 600) GetAX(rab,AX_PRESENT_POSITION); 250
    PutAX(tub,AX_GOAL_POSITION,350); //reouvre legerement le tub
    __delay_ms(50);
//        while (  != 350) GetAX(tub,AX_PRESENT_POSITION);
    PutAX(pince,AX_GOAL_POSITION,255); //ouvre la pince
    __delay_ms(50);
//        while (   != 255) GetAX(pince,AX_PRESENT_POSITION);
    PutAX(asc,AX_GOAL_POSITION,945); //descent la pince
    __delay_ms(1000);
//        while (   != 945) GetAX(asc,AX_PRESENT_POSITION);
    PutAX(pince,AX_GOAL_POSITION,170); //ferme la pince
    __delay_ms(1000);
//        while (   != 170) GetAX(pince,AX_PRESENT_POSITION);
    PutAX(asc,AX_GOAL_POSITION,320); //remonte la pince
    __delay_ms(1000);
    
//        while (   != 320) GetAX(asc,AX_PRESENT_POSITION);
    PutAX(tub,AX_GOAL_POSITION,270); //referme le tube
    __delay_ms(1000);
//        while (  != 270) GetAX(tub,AX_PRESENT_POSITION);
    PutAX(pince,AX_GOAL_POSITION,255); //ouvre la pince
    __delay_ms(1000);
//        while (   != 255) GetAX(pince,AX_PRESENT_POSITION);

    SendDone();
    }
    else {
        SendFailAX12();


    }
}

void charg_last_spot(void)
{
//int k;
    PutAX(rabd,AX_GOAL_POSITION,300); //rabat la piece 700
    __delay_ms(700);
//        while (  != 330) GetAX(rab,AX_PRESENT_POSITION); 200
    PutAX(rabd,AX_GOAL_POSITION,620); //reouvre
    __delay_ms(700);
    PutAX(rabg,AX_GOAL_POSITION,850); //rabat la piece 700
    __delay_ms(700);
//        while (  != 330) GetAX(rab,AX_PRESENT_POSITION); 200
    PutAX(rabg,AX_GOAL_POSITION,390); //reouvre
    __delay_ms(50);
//        while (  != 350) GetAX(tub,AX_PRESENT_POSITION);
    PutAX(pince,AX_GOAL_POSITION,255); //ouvre la pince
    __delay_ms(50);
//        while (   != 255) GetAX(pince,AX_PRESENT_POSITION);
    PutAX(asc,AX_GOAL_POSITION,945); //descent la pince
    __delay_ms(1000);
//        while (   != 945) GetAX(asc,AX_PRESENT_POSITION);
    PutAX(pince,AX_GOAL_POSITION,170); //ferme la pince
    __delay_ms(1000);

    SendDone();
}

void release (void) {

    PutAX(pince,AX_GOAL_POSITION,255); //entre-ouvre pince
    __delay_ms(700);
    PutAX(asc,AX_GOAL_POSITION,320); //remonte la pince
    __delay_ms(1000);
    PutAX(tub,AX_GOAL_POSITION,700); //ouvre reservoir
    __delay_ms(700);
    PutAX(pince,AX_GOAL_POSITION,500); //entre-ouvre pince
    __delay_ms(700);

    SendDone();
}

void close_claws(void) { // fonction qui permet la fermeture des pinces à la volée
    PutAX(rabd,AX_GOAL_POSITION,200);
    __delay_ms(700);
    PutAX(rabg,AX_GOAL_POSITION,750);
    __delay_ms(700);
}

void open_claws(void) { // fonction qui permet la fermeture des pinces à la volée
    PutAX(rabg, AX_GOAL_POSITION, 390);
    __delay_ms(500);
    PutAX(rabd, AX_GOAL_POSITION, 620);
    __delay_ms(500);
}

void open_clap(void) {
    PutAX(clap,AX_GOAL_POSITION,830); //rabat la piece 700
    __delay_ms(700);
    SendDone();
}

void close_clap(void) {
    PutAX(clap,AX_GOAL_POSITION,512); //rabat la piece 700
    __delay_ms(700);
    SendDone();
}

void open_popcorn(void) {
    PutAX(popcorn,AX_GOAL_POSITION,420); //rabat la piece 700
    __delay_ms(700);
    SendDone();
}

void close_popcorn(void) {
    PutAX(popcorn,AX_GOAL_POSITION,612); //rabat la piece 700
    __delay_ms(700);
    SendDone();
}
/******************************************************************************/