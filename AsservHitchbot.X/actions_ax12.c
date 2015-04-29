#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include "user.h"        /* Function / Parameters                           */
#include <libpic30.h>
#include "ax12.h"
#include <uart.h>
#include <delay.h>
#include "actions_ax12.h"

#define maxtork 400

/******************************************************************************/
/*************************** Arm Specification ********************************/
/******************************************************************************/

void choose_arm(int arm) {

}

/******************************************************************************/
/****************************** Init Position *********************************/
/******************************************************************************/

void Init_ax12() {

    PutAX(rabd, AX_TORQUE_LIMIT, maxtork);
    __delay_ms(40);
    PutAX(rabg, AX_TORQUE_LIMIT, 400);
    __delay_ms(40);
    PutAX(pince, AX_TORQUE_LIMIT, 500);
    __delay_ms(40);
    PutAX(asc, AX_TORQUE_LIMIT, 900);
    __delay_ms(40);
    PutAX(tub, AX_TORQUE_LIMIT, 600);
    __delay_ms(40);

    PutAX(rabd, AX_MOVING_SPEED, 850);
    __delay_ms(40);
    PutAX(rabg, AX_MOVING_SPEED, 850);
    __delay_ms(40);
    PutAX(pince, AX_MOVING_SPEED, 800);
    __delay_ms(40);
    PutAX(asc, AX_MOVING_SPEED, 800);
    __delay_ms(40);
    PutAX(tub, AX_MOVING_SPEED, 450);
    __delay_ms(40);

    PutAX(asc, AX_GOAL_POSITION, 320);
    __delay_ms(500);
    PutAX(rabd, AX_GOAL_POSITION, 620);
    __delay_ms(500);
    PutAX(rabg, AX_GOAL_POSITION, 390);
    __delay_ms(500);
    PutAX(pince, AX_GOAL_POSITION, 260);
    __delay_ms(500);
    PutAX(tub, AX_GOAL_POSITION, 400);

    __delay_ms(40);

}

void charg_spot(void)
{
int k;
    PutAX(rabd,AX_GOAL_POSITION,450); //rabat la piece 700
    __delay_ms(700);
//        while (  != 330) GetAX(rab,AX_PRESENT_POSITION); 200
    PutAX(rabd,AX_GOAL_POSITION,600); //reouvre
    __delay_ms(700);
    PutAX(rabg,AX_GOAL_POSITION,690); //rabat la piece 700
    __delay_ms(700);
//        while (  != 330) GetAX(rab,AX_PRESENT_POSITION); 200
    PutAX(rabg,AX_GOAL_POSITION,390); //reouvre
    __delay_ms(50);
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
}


/******************************************************************************/