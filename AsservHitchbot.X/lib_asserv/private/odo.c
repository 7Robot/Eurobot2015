#include "extern_globals_asserv.h"
#include "odo.h"
#include "asserv.h"
#include "../lib_asserv_default.h"
#include <math.h>
#include "tools.h"

/******************************    Variables    *******************************/
volatile Odo odo;

/******************************    Fonctions    *******************************/

// initialiser l'odométrie
void odo_init(){
    OdoCoefs coefs = DEFAULT_ODO_COEFS;
    OdoTics tics = {0,0};
    odo_set_coefs(&odo,coefs);
    odo.tics = tics;
    odo_set_state(&odo,&motionState);
    odo_set_period(&odo,DEFAULT_PERIOD);
}

// assigner des valeurs aux coefs (relations tic/mètre et entraxe)
void odo_set_coefs (Odo *odo, OdoCoefs coefs){odo->coefs = coefs;}
void odo_set_tic_by_meter(Odo *odo, int tic_by_meter){
    odo->coefs.tic_by_meter = tic_by_meter;
    odo->coefs.meter_by_tic = 1/((float)tic_by_meter);
}
void odo_set_spacing(Odo *odo, float spacing){odo->coefs.spacing = spacing;}


// lier l'odométrie à un état du robot (positions, vitesses, ...)
void odo_set_state(Odo *odo, MotionState *state){odo->state = state;}

// indiquer la période entre 2 mesures pour l'odométrie
void odo_set_period(Odo *odo, float period){odo->period = period;}

// MAJ de l'état du robot avec les valeurs des QEI gauche et droit
void odo_step(Odo *odo, int qei_g, int qei_d){
    // calculs intermédiaires des déplacements gauches et droites
    float dg = (float)(qei_g-(odo->tics).tics_g)*(odo->coefs).meter_by_tic;
    float dd = (float)(qei_d-(odo->tics).tics_d)*(odo->coefs).meter_by_tic;
    // distance et angle de déplacement depuis le dernier step
    float d = (dd+dg)/2;
    float dt = (dd-dg)/(odo->coefs).spacing;

    // sauvegarde des anciennes vitesses
    float v = odo->state->speed.v;
    float vt = odo->state->speed.vt;

    // maj des tics
    odo->tics.tics_g = qei_g;
    odo->tics.tics_d = qei_d;

    // maj des positions
    odo->state->pos.x += d*cos(odo->state->pos.t + 0.5*dt); // calcul centré
    odo->state->pos.y += d*sin(odo->state->pos.t + 0.5*dt); // calcul centré
    odo->state->pos.t += dt;
    odo->state->pos.t = principal_angle(odo->state->pos.t);

    // maj des vitesses
    odo->state->speed.v = d/(odo->period);
    odo->state->speed.vt = dt/(odo->period);

    // maj des accélérations
    odo->state->acc.a = odo->state->speed.v - v;
    odo->state->acc.at = odo->state->speed.vt - vt;
    odo->state->acc.v_vt = (odo->state->speed.v)*(odo->state->speed.vt);
}