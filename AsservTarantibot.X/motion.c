/*
#include "config.h"
#include "motion.h"
#include "odo.h"
#include "asserv.h"

extern Speed speed_current; // la vitesse actuelle déterminé par l'odométrie
extern Speed speed_rampe; // vitesse théorique générée par l'asserv
extern Acceleration acc_current; // accélérationa actuelle
extern Speed speed_goal;// vitesse objectif

int motion_state = 0; // variable contenant la nature de l'asserv à un instant donné 0: roue libre : 1 vitesse : 2 : position
//initialiser l'asservissement
void motion_init() {
    motion_state = 0;
    odo_init();
    asserv_init();
}

void motion_step(int tics_g,int tics_d, float *cmd_g, float *cmd_d) {
    odo_step(tics_g,tics_d); // step de l'odo
    switch (motion_state)
    {
        case 0 :
            *cmd_g = 0;
            *cmd_d = 0;
          break;
        case 1 :
            rampe(speed_current); // génére les vitesses consignes à atteindre
            speed_asserv_step(speed_current,acc_current,cmd_g,cmd_d);
        case 2 : break;
    }


}
void motion_stop(void) {
    motion_state=0;// on passe en asserv en vitesse
}

void motion_speed(Speed speed){
    motion_state=1;// on passe en asserv en vitesse
    init_rampe(speed_current,speed,acc_current);
}
*/