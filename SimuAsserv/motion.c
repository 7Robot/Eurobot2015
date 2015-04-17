#include "config.h"
#include "motion.h"
#include "odo.h"
#include "asserv.h"

extern Speed speed_current; // la vitesse actuelle déterminé par l'odométrie
extern Speed speed_rampe; // vitesse théorique générée par l'asserv
extern Acceleration acc_current; // accélérationa actuelle
extern Speed speed_goal;// vitesse objectif

//initialiser l'asservissement
void motion_init() {
    //Position pos_init = {0.0.0};
    odo_init();
    asserv_init();
}

void motion_step(int tics_g,int tics_d, float *cmd_g, float *cmd_d) {
    odo_step(tics_g,tics_d); // step de l'odo
    rampe(speed_current); // génére les vitesses consignes à atteindre
    speed_asserv_step(speed_current,acc_current,cmd_g,cmd_d);

}

void motion_speed(Speed speed){
    init_rampe(speed_current,speed,acc_current);
}


