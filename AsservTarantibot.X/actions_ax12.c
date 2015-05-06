#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include "user.h"        /* Function / Parameters                           */
#include <libpic30.h>
#include "ax12.h"
#include <uart.h>
#include <delay.h>
#include "actions_ax12.h"



/******************************************************************************/
/*************************** Arm Specification ********************************/
/******************************************************************************/

void choose_arm(int arm) {

}

/******************************************************************************/
/****************************** Init Position *********************************/
/******************************************************************************/

void init_ax12() {

    PutAX(socle, AX_TORQUE_LIMIT, 900);
    __delay_ms(40);
    PutAX(haut, AX_TORQUE_LIMIT, 900);
    __delay_ms(40);
    PutAX(verseur_d, AX_TORQUE_LIMIT, 900);
    __delay_ms(40);
    PutAX(pince_d, AX_TORQUE_LIMIT, 900);
    __delay_ms(40);
    PutAX(coude, AX_TORQUE_LIMIT, 900);
    __delay_ms(40);
    PutAX(verseur_g, AX_TORQUE_LIMIT, 900);
    __delay_ms(40);
    PutAX(pince_g, AX_TORQUE_LIMIT, 500);
    __delay_ms(40);


    PutAX(socle, AX_MOVING_SPEED, 100);
    __delay_ms(40);
    PutAX(haut, AX_MOVING_SPEED, 100);
    __delay_ms(40);
    PutAX(verseur_d, AX_MOVING_SPEED, 1000);
    __delay_ms(40);
    PutAX(pince_d, AX_MOVING_SPEED, 100);
    __delay_ms(40);
    PutAX(coude, AX_MOVING_SPEED, 500);
    __delay_ms(40);
    PutAX(verseur_g, AX_MOVING_SPEED, 1000);
    __delay_ms(40);
    PutAX(pince_g, AX_MOVING_SPEED, 100);
    __delay_ms(40);

    PutAX(socle, AX_GOAL_POSITION, 800);
    __delay_ms(40);
    PutAX(haut, AX_GOAL_POSITION, 204);
    __delay_ms(40);
    PutAX(verseur_d, AX_GOAL_POSITION, 250);
    __delay_ms(40);
    PutAX(pince_d, AX_GOAL_POSITION, 550);
    __delay_ms(1000);
    PutAX(verseur_g, AX_GOAL_POSITION, 800);
    __delay_ms(40);
    PutAX(pince_g, AX_GOAL_POSITION, 400);
    __delay_ms(200);
    PutAX(coude, AX_GOAL_POSITION, 250);
    __delay_ms(1000);

}

void deploy (void){

    PutAX(coude, AX_GOAL_POSITION, 511);
    __delay_ms(1000);
    PutAX(socle, AX_GOAL_POSITION, 551);
    __delay_ms(40);
    PutAX(haut, AX_GOAL_POSITION, 471);
    __delay_ms(1500);
    PutAX(verseur_g, AX_GOAL_POSITION, 471);
    __delay_ms(40);
    PutAX(verseur_d, AX_GOAL_POSITION, 550);
    __delay_ms(1000);
    PutAX(verseur_g, AX_GOAL_POSITION, 800);
    __delay_ms(40);
    PutAX(verseur_d, AX_GOAL_POSITION, 250);
    __delay_ms(1000);
}

void lacher (void){

    PutAX(pince_g, AX_GOAL_POSITION, 350);
    __delay_ms(40);
    PutAX(pince_d, AX_GOAL_POSITION, 600);
    __delay_ms(1000);
}

void ranger (void){

    PutAX(pince_g, AX_GOAL_POSITION, 400);
    __delay_ms(40);
    PutAX(pince_d, AX_GOAL_POSITION, 550);
    __delay_ms(1000);
    PutAX(socle, AX_GOAL_POSITION, 800);
    __delay_ms(40);
    PutAX(haut, AX_GOAL_POSITION, 204);
    __delay_ms(1000);
    PutAX(coude, AX_GOAL_POSITION, 250);
    __delay_ms(1000);
}

/******************************************************************************/
