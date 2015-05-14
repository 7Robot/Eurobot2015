#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <stdio.h>
#include <uart.h>
#include <delay.h>

#include "main.h"


#define maxtork_claw 500
#define maxspeed_claw 650
#define delay_ax 30

/******************************************************************************/
/*************************** Arm Specification ********************************/
/******************************************************************************/


/******************************************************************************/
/****************************** Init Position *********************************/
/******************************************************************************/

volatile int Num_Action_Done = 0;
volatile int Num_Action_ToDo = 0;
volatile char Tab_Actions_ToDo [NUM_ACTIONS_BUFFER] = {0};

void Add_Action_AX12(char Action_ToDo)
{
    int num = Num_Action_ToDo;
    num++;
    if (num == NUM_ACTIONS_BUFFER) {
        num = 0;
    }
    Tab_Actions_ToDo[num] = Action_ToDo;
    Num_Action_ToDo = num;
}

void Faire_Actions_AX12(void)
{
    int num = Num_Action_Done;
    char Action_ToDo;
    if (num != Num_Action_ToDo && Delay_90 < 90000) {
        num++;
        if (num == NUM_ACTIONS_BUFFER) {
            num = 0;
        }
        Action_ToDo = Tab_Actions_ToDo[num];
        switch (Action_ToDo)
        {
            case AX12_INIT_AX12 :
                Init_ax12();
                break;
            case AX12_CHARG_SPOT :
                charg_spot();
                break;
            case AX12_CHARG_LAST_SPOT :
                charg_last_spot();
                break;
            case AX12_RELEASE:
                release();
                break;
            case AX12_CLOSE_CLAWS:
                close_claws();
                break;
            case AX12_OPEN_CLAWS:
                open_claws();
                break;
            case AX12_OPEN_POPCORN:
                open_popcorn();
                break;
            case AX12_CLOSE_POPCORN:
                close_popcorn();
                break;
            case AX12_CLOSE_TUB:
                close_tub();
                break;
            case AX12_CLOSE_CLAPR:
                close_clap_r();
                break;
            case AX12_OPEN_CLAPR:
                open_clap_r();
                break;
            case AX12_CLOSE_CLAPL:
                close_clap_l();
                break;
            case AX12_OPEN_CLAPL:
                open_clap_l();
                break;
        }
        Num_Action_Done = num;
    }
}





void Init_ax12() {

    PutAX(rabd, AX_TORQUE_LIMIT, maxtork_claw);
    __delay_ms(delay_ax);
    PutAX(rabg, AX_TORQUE_LIMIT, maxtork_claw);
    __delay_ms(delay_ax);
    PutAX(pince, AX_TORQUE_LIMIT, 500);
    __delay_ms(delay_ax);
    PutAX(asc, AX_TORQUE_LIMIT, 900);
    __delay_ms(delay_ax);
    PutAX(tub, AX_TORQUE_LIMIT, 700);
    __delay_ms(delay_ax);
    PutAX(clapr, AX_TORQUE_LIMIT, maxtork_claw);
    __delay_ms(delay_ax);
    PutAX(clapl, AX_TORQUE_LIMIT, maxtork_claw);
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
    PutAX(clapl, AX_MOVING_SPEED, 1000);
    __delay_ms(delay_ax);
    PutAX(clapr, AX_MOVING_SPEED, 1000);
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
    PutAX(clapl, AX_GOAL_POSITION, 512);
    __delay_ms(40);
    PutAX(clapr, AX_GOAL_POSITION, 512);
    __delay_ms(40);
    PutAX(popcorn, AX_GOAL_POSITION, 612);
    __delay_ms(40);

}

void charg_spot(void)
{
//int k;
    if(!PIN_TEAM) {
        PutAX(rabd,AX_GOAL_POSITION,300); //rabat la piece 700
        __delay_ms(700);
        PutAX(rabd,AX_GOAL_POSITION,620); //reouvre
        __delay_ms(500);
        PutAX(rabg,AX_GOAL_POSITION,850); //rabat la piece 700
        __delay_ms(700);
        PutAX(rabg,AX_GOAL_POSITION,390); //reouvre
        __delay_ms(50);
    }
    else {
        PutAX(rabg,AX_GOAL_POSITION,850); //rabat la piece 700
        __delay_ms(700);
        PutAX(rabg,AX_GOAL_POSITION,390); //reouvre
        __delay_ms(500);
        PutAX(rabd,AX_GOAL_POSITION,300); //rabat la piece 700
        __delay_ms(700);
        PutAX(rabd,AX_GOAL_POSITION,620); //reouvre
        __delay_ms(50);
    }

    if (PORTAbits.RA9 == 1) {

        PutAX(tub,AX_GOAL_POSITION,350); //reouvre legerement le tub
        __delay_ms(50);
        PutAX(pince,AX_GOAL_POSITION,255); //ouvre la pince
        __delay_ms(50);
        PutAX(asc,AX_GOAL_POSITION,945); //descent la pince
        __delay_ms(700);
        PutAX(pince,AX_GOAL_POSITION,170); //ferme la pince
        __delay_ms(300);
        PutAX(asc,AX_GOAL_POSITION,320); //remonte la pince
        __delay_ms(850);
        PutAX(tub,AX_GOAL_POSITION,270); //referme le tube
        __delay_ms(300);
        PutAX(pince,AX_GOAL_POSITION,255); //ouvre la pince
        __delay_ms(50);

        SendDone();
    }
    else {
        SendFailAX12();
    }
}

void charg_last_spot(void)
{
    if(!PIN_TEAM) {
        PutAX(rabd,AX_GOAL_POSITION,300); //rabat la piece 700
        __delay_ms(700);
        PutAX(rabd,AX_GOAL_POSITION,620); //reouvre
        __delay_ms(500);
        PutAX(rabg,AX_GOAL_POSITION,850); //rabat la piece 700
        __delay_ms(700);
        PutAX(rabg,AX_GOAL_POSITION,390); //reouvre
        __delay_ms(50);
    }
    else {
        PutAX(rabg,AX_GOAL_POSITION,850); //rabat la piece 700
        __delay_ms(700);
        PutAX(rabg,AX_GOAL_POSITION,390); //reouvre
        __delay_ms(500);
        PutAX(rabd,AX_GOAL_POSITION,300); //rabat la piece 700
        __delay_ms(700);
        PutAX(rabd,AX_GOAL_POSITION,620); //reouvre
        __delay_ms(50);
    }
    PutAX(pince,AX_GOAL_POSITION,255); //ouvre la pince
    __delay_ms(50);
    PutAX(asc,AX_GOAL_POSITION,945); //descent la pince
    __delay_ms(600);
    PutAX(pince,AX_GOAL_POSITION,170); //ferme la pince
    __delay_ms(50);

    SendDone();
}

void release (void) {

    PutAX(pince,AX_GOAL_POSITION,255); //entre-ouvre pince
    __delay_ms(300);
    PutAX(asc,AX_GOAL_POSITION,320); //remonte la pince
    __delay_ms(600);
    PutAX(tub,AX_GOAL_POSITION,700); //ouvre reservoir
    __delay_ms(300);
    PutAX(pince,AX_GOAL_POSITION,500); //ouvre pince
    __delay_ms(300);

    SendDone();
}

void close_claws(void) { // fonction qui permet la fermeture des pinces à la volée
    PutAX(rabd,AX_GOAL_POSITION,200);
    __delay_ms(500);
    PutAX(rabg,AX_GOAL_POSITION,750);
    __delay_ms(50);
}

void open_claws(void) { // fonction qui permet la fermeture des pinces à la volée
    PutAX(rabg, AX_GOAL_POSITION, 390);
    __delay_ms(500);
    PutAX(rabd, AX_GOAL_POSITION, 620);
    __delay_ms(50);
}

void open_clap_r(void) {
    PutAX(clapr,AX_GOAL_POSITION,194); //rabat la piece 700
    __delay_ms(100);
}

void close_clap_r(void) {
    PutAX(clapr,AX_GOAL_POSITION,512); //rabat la piece 700
    __delay_ms(100);
}

void open_clap_l(void) {
    PutAX(clapl,AX_GOAL_POSITION,830); //rabat la piece 700
    __delay_ms(100);
}

void close_clap_l(void) {
    PutAX(clapl,AX_GOAL_POSITION,512); //rabat la piece 700
    __delay_ms(100);
}

void open_popcorn(void) {
    PutAX(popcorn,AX_GOAL_POSITION,405); //rabat la piece 700
    __delay_ms(50);
    SendDone();
}

void close_popcorn(void) {
    PutAX(popcorn,AX_GOAL_POSITION,612); //rabat la piece 700
    __delay_ms(50);
    SendDone();
}

void close_tub(void) { // fonction qui permet de refermer le tub de manière asynchrone
    PutAX(tub,AX_GOAL_POSITION,270); //referme le tube
    __delay_ms(250);
}
/******************************************************************************/