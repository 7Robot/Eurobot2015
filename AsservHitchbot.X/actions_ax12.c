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

    PutAX(rab, AX_TORQUE_LIMIT, maxtork);
    __delay_ms(40);
    PutAX(pince, AX_TORQUE_LIMIT, 500);
    __delay_ms(40);
    PutAX(asc, AX_TORQUE_LIMIT, 900);
    __delay_ms(40);
    PutAX(tub, AX_TORQUE_LIMIT, 600);
    __delay_ms(40);

    PutAX(rab, AX_MOVING_SPEED, 500);
    __delay_ms(40);
    PutAX(pince, AX_MOVING_SPEED, 500);
    __delay_ms(40);
    PutAX(asc, AX_MOVING_SPEED, 800);
    __delay_ms(40);
    PutAX(tub, AX_MOVING_SPEED, 450);
    __delay_ms(40);

    PutAX(asc, AX_GOAL_POSITION, 320);
    __delay_ms(1000);
    PutAX(rab, AX_GOAL_POSITION, 600);
    __delay_ms(500);
    PutAX(pince, AX_GOAL_POSITION, 260);
    __delay_ms(1000);
    PutAX(tub, AX_GOAL_POSITION, 400);

    __delay_ms(40);

}

void charg_spot(void)
{
    float pos_checker = 0;
/*
    PutAX(rab,AX_GOAL_POSITION,330); //rabat la piece
        while ( pos_checker = GetAX(rab,AX_PRESENT_POSITION) != 330){    }
    PutAX(rab,AX_GOAL_POSITION,600); //reouvre
        while ( pos_checker = GetAX(rab,AX_PRESENT_POSITION) != 600){    }
    PutAX(tub,AX_GOAL_POSITION,350); //reouvre legerement le tub
        while ( pos_checker = GetAX(tub,AX_PRESENT_POSITION) != 350){    }
    PutAX(pince,AX_GOAL_POSITION,255); //ouvre la pince
        while ( pos_checker = GetAX(pince,AX_PRESENT_POSITION) != 255){    }
    PutAX(asc,AX_GOAL_POSITION,945); //descent la pince
        while ( pos_checker = GetAX(asc,AX_PRESENT_POSITION) != 945){    }
    PutAX(pince,AX_GOAL_POSITION,170); //ferme la pince
        while ( pos_checker = GetAX(pince,AX_PRESENT_POSITION) != 170){    }
    PutAX(tub,AX_GOAL_POSITION,400); //remonte a moitié la piece et bloque
        while ( pos_checker = GetAX(tub,AX_PRESENT_POSITION) != 400){    }
    PutAX(asc,AX_GOAL_POSITION,320); //remonte la pince
        while ( pos_checker = GetAX(asc,AX_PRESENT_POSITION) != 320){    }
    PutAX(tub,AX_GOAL_POSITION,270); //referme le tube
        while ( pos_checker = GetAX(tub,AX_PRESENT_POSITION) != 270){    }
    PutAX(pince,AX_GOAL_POSITION,255); //ouvre la pince
        while ( pos_checker = GetAX(pince,AX_PRESENT_POSITION) != 255){    }*/

    PutAX(rab,AX_GOAL_POSITION,330); //rabat la piece
    __delay_ms(2000);
    PutAX(rab,AX_GOAL_POSITION,600); //reouvre
    __delay_ms(1000);
    PutAX(tub,AX_GOAL_POSITION,350); //reouvre legerement le tub
    __delay_ms(1000);
    PutAX(pince,AX_GOAL_POSITION,255); //ouvre la pince
    __delay_ms(1000);
    PutAX(asc,AX_GOAL_POSITION,945); //descent la pince
    __delay_ms(1000);
    PutAX(pince,AX_GOAL_POSITION,170); //ferme la pince
    __delay_ms(2000);
    PutAX(tub,AX_GOAL_POSITION,400); //remonte a moitié la piece et bloque
    __delay_ms(1000);
    PutAX(asc,AX_GOAL_POSITION,320); //remonte la pince
    __delay_ms(2000);
    PutAX(tub,AX_GOAL_POSITION,270); //referme le tube
    __delay_ms(2000);
    PutAX(pince,AX_GOAL_POSITION,255); //ouvre la pince
    __delay_ms(1000);
}


/******************************************************************************/
