/*
#include "config.h"
#include "odo.h"
#include "asserv.h"
#include "math.h"
#include "motion.h"// pour avoir les structures
#include <stdio.h>
#include "asserv.h"
//Variable globale//
Speed speed_rampe;
Speed speed_goal;

Error error_speed_v = {0,0,0};
Error error_speed_vt = {0,0,0};

PID pid_speed_v = {1000,60,10};
PID pid_speed_vt = {1000,60,10};
extern FILE* fichier_v ;
extern FILE* fichier_vt ;
int asserv_done = 0;
int rampe_statev = 0;
int rampe_statevt = 0;
float C_v=0,C_vt=0;

void asserv_init(){ // remise à zéro pour une nouvelle consigne
    speed_rampe.v=0;
    speed_rampe.vt=0;
    speed_goal.v=0;
    speed_goal.vt=0;
    asserv_done = 0;
    C_v=0;
    C_vt=0;
    //error_speed_v = {0,0,0};
    //error_speed_vt = {0,0,0};
}


void speed_asserv_step(Speed speed_current,Acceleration acc_current, float *cmg, float *cmd) {
    float E_v,E_vt;


    E_v=speed_rampe.v-speed_current.v;
    E_vt=speed_rampe.vt-speed_current.vt;

    //printf("Spd_rmp%f Spd_cur%f \n\r",speed_rampe.v,speed_current.v);
    //printf("E_v%f E_vt%f \n\r",E_v,E_vt);

    
    //if(E_v<speed_threshold && E_vt<speed_threshold){ // asserv_done = 1 si on a atteint la vitesse voulue
    //    asserv_done=1;
    //    printf("asserv terminée !");
    //    printf("\n");
    //}
    

    error_speed_v.Ed= E_v-error_speed_v.Ep; // écriture des erreurs v
    error_speed_v.Ei= error_speed_v.Ep+E_v;
    error_speed_v.Ep= E_v;

    error_speed_vt.Ed= E_vt-error_speed_vt.Ep; // écriture des erreurs vt
    error_speed_vt.Ei= error_speed_vt.Ep+E_vt;
    error_speed_vt.Ep= E_vt;

    //application de la correction
    C_v = error_speed_v.Ep*pid_speed_v.Kp + error_speed_v.Ei*pid_speed_v.Ki -error_speed_v.Ed*pid_speed_v.Kd;
    C_vt = error_speed_vt.Ep*pid_speed_vt.Kp + error_speed_vt.Ei*pid_speed_vt.Ki -error_speed_vt.Ed*pid_speed_vt.Kd;

    //printf("Cv%f Cvt%f \n\r",C_v,C_vt);

    // *cmg = (2*period*C_v-C_vt*spacing*period)/2;
    // *cmd = (2*period*C_v+C_vt*spacing*period)/2;
    *cmg = C_v-C_vt;
    *cmd = C_v+C_vt;

    }



void rampe(Speed speed_current){


    if (speed_rampe.v<=speed_goal.v && rampe_statev == 0 ) { // on vérifie si on est sur la pente ou au plat de la rampe
        speed_rampe.v= speed_rampe.v + DEFAULT_CONSTRAINT_A_MAX*period; // génération de l'échelon suivant de l'asserv
    }
    else if (speed_rampe.v>speed_goal.v && rampe_statev == 1 ) {
        speed_rampe.v= speed_rampe.v - DEFAULT_CONSTRAINT_A_MAX*period; // génération de l'échelon suivant de l'asserv
    }

    if (speed_rampe.vt<=speed_goal.vt && rampe_statevt == 0) { // on vérifie si on est sur la pente ou au plat de la rampe
        speed_rampe.vt= speed_rampe.vt + DEFAULT_CONSTRAINT_AT_MAX*period; // génération de l'échelon suivant de l'asserv
    }
    else if (speed_rampe.vt>speed_goal.vt && rampe_statevt == 1) {
        speed_rampe.vt= speed_rampe.vt - DEFAULT_CONSTRAINT_AT_MAX*period; // génération de l'échelon suivant de l'asserv
    }


}

void init_rampe(Speed speed_current,Speed speed_consigne,Acceleration acc_current){
//    #speed_rampe.v= DEFAULT_CONSTRAINT_A_MAX*period + speed_current.v; // génération du premier échelon de l'asserv
  //  #speed_rampe.vt= DEFAULT_CONSTRAINT_AT_MAX*period + speed_current.vt;

    speed_goal.v=speed_consigne.v; // on fixe les objectifs
    speed_goal.vt=speed_consigne.vt;

    if(speed_goal.v > speed_current.v){ // rampe en v positive
        rampe_statev = 0;
    }
    else { // rampe négative
        rampe_statev=1;
    }

    if(speed_goal.vt>speed_current.vt){ // rampe en v positive
        rampe_statevt = 0;
    }
    else { // rampe négative
        rampe_statevt=1;
    }

//    printf("speed_goal v : %f \n", speed_goal.v);
 //   printf("speed_goal vt: %f \n", speed_goal.vt);
 //   printf("\n");

}

*/