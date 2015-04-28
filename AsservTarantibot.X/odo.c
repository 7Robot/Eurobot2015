#include "config.h"
#include "odo.h"
#include "asserv.h"
#include "math.h"
#include "motion.h"// pour avoir les structures
#include <stdio.h>
//////////////////////////////Variables//////////////////////////////////
Position pos_old;
Speed speed_old;
Acceleration acc_old;


Position pos_current;
Speed speed_current;
Acceleration acc_current;


int tics_g_old = 0;
int tics_d_old = 0;
//////////////////////////////Fonctions///////////////////////////////////
void odo_init(){ // démarrage de l'odométrie
    pos_old.x=0;
    pos_old.y=0;
    pos_old.t=0;
    speed_old.vt=0;
    speed_old.v=0;
    acc_old.a=0;
    acc_old.at=0;
    acc_old.v_vt=0;

    pos_current.x=0;
    pos_current.y=0;
    pos_current.t=0;
    speed_current.vt=0;
    speed_current.v=0;
    acc_current.a=0;
    acc_current.at=0;
    acc_current.v_vt=0;

    tics_g_old = 0;
    tics_d_old = 0;

}

void odo_step(int tics_g,int tics_d) {
    step(); // old = new
    float diff_g = (tics_g - tics_g_old)*meter_by_tic;
    float diff_d = (tics_d - tics_d_old)*meter_by_tic;

    tics_g_old=tics_g;
    tics_d_old=tics_d;

    float distance = (diff_g+diff_d)/2;
    float angle = (diff_d-diff_g)/spacing;

    //mise a jour de la position
    pos_current.x =pos_old.x+distance*cos(pos_old.t+0.5*angle);
    pos_current.y =pos_old.y+distance*sin(pos_old.t+0.5*angle);
    pos_current.t =decalage_angulaire(pos_old.t+angle);

    //mise a jour de la vitesse
    speed_current.v=distance/period;
    speed_current.vt=angle/period;

    acc_current.a=speed_current.v-speed_old.v;
    acc_current.at=speed_current.vt-speed_old.vt;
    acc_current.v_vt=speed_current.vt*speed_current.v;


    //DEBUG


}

void step(void) {
    pos_old.x=pos_current.x;
    pos_old.y=pos_current.y;
    pos_old.t=pos_current.t;

    speed_old.v=speed_current.v;
    speed_old.vt=speed_current.vt;

    acc_old.a=acc_current.a;
    acc_old.at=acc_current.at;
    acc_old.v_vt=acc_current.v_vt;
}

float decalage_angulaire(float angle){
    float alpha;
    if (fabs(angle)< PI){return angle;}
    else {
        alpha = fmod(angle,2*PI);
        if (alpha<-PI){alpha += 2*PI;}
        if (alpha>PI){alpha -= 2*PI;}
        return alpha;
    }
}

