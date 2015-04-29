#include "extern_globals_asserv.h"
#include "asserv.h"
#include "odo.h"
#include "pid.h"
#include "../lib_asserv_default.h"
#include "debug.h"
#include "tools.h"
#include <math.h>


/******************************    Variables    *******************************/
volatile int asserv_mode;
volatile PositionAsserv pos_asserv;
volatile SpeedAsserv speed_asserv;
volatile AngleAsserv angle_asserv;



/******************************    Fonctions    *******************************/

// initialiser le mode et les différents asservissement
void asserv_init(){
    asserv_mode = DEFAULT_ASSERV_MODE;

    // PID pour l'asserv en vitesse (delta)
    Pid pid_delta;
    PidCoefs coefs_delta = DEFAULT_PID_COEFS_DELTA;
    PidState state_delta = {0,0,0,0,0,DEFAULT_PID_MAX_INT_DELTA};
    PidEps eps_delta = DEFAULT_PID_EPS_DELTA;
    pid_set_coefs(&pid_delta,coefs_delta);
    pid_set_state(&pid_delta, state_delta);
    pid_set_eps(&pid_delta, eps_delta);
    pid_set_order(&pid_delta, 0);

    // PID pour l'asserv en vitesse angulaire (alpha)
    Pid pid_alpha;
    PidCoefs coefs_alpha = DEFAULT_PID_COEFS_ALPHA;
    PidState state_alpha = {0,0,0,0,0,DEFAULT_PID_MAX_INT_ALPHA};
    PidEps eps_alpha = DEFAULT_PID_EPS_ALPHA;
    pid_set_coefs(&pid_alpha,coefs_alpha);
    pid_set_state(&pid_alpha, state_alpha);
    pid_set_eps(&pid_alpha, eps_alpha);
    pid_set_order(&pid_alpha, 0);

    // initialisation de l'asservissement en position
    pos_asserv.pos_order = (Position){0,0,0};
    pos_asserv.stop_distance = DEFAULT_STOP_DISTANCE;
    // respect des contraintes d'accélération max avec ce coef
    pos_asserv.kp = 1.6;
    pos_asserv.state = &motionState;
    pos_asserv.constraint = &motionConstraint;
    pos_asserv.done = 0;
    pos_asserv.distance = (DistanceDebug){0,0};
    // initialisation de l'asservissement en vitesse
    speed_asserv.speed_order = (Speed){0,0};
    speed_asserv.speed_order_constrained = (Speed){0,0};
    speed_asserv.state = &motionState;
    speed_asserv.constraint = &motionConstraint;
    speed_asserv.pid_delta = pid_delta;
    speed_asserv.pid_alpha = pid_alpha;
    speed_asserv.done = 0;
    // initialisation de l'asservissement en angle
    angle_asserv.angle_order = 0;
    angle_asserv.state = &motionState;
    angle_asserv.constraint = &motionConstraint;
    angle_asserv.pid_alpha = pid_alpha;
    angle_asserv.done = 0;
}

// assigner un PID et des contraintes à un asservissement
void set_speedAsserv_pids(Pid pid_delta, Pid pid_alpha){
    speed_asserv.pid_delta = pid_delta;
    speed_asserv.pid_alpha = pid_alpha;
}
void set_speedAsserv_constraint(MotionConstraint *constraint){ speed_asserv.constraint = constraint; }

// choisir le mode d'asservissement (désactivé, en position, en vitesse)
void set_asserv_off(){asserv_mode = ASSERV_MODE_OFF;}
void set_asserv_pos_mode(){asserv_mode = ASSERV_MODE_POS;}
void set_asserv_speed_mode(){asserv_mode = ASSERV_MODE_SPEED;}
void set_asserv_angle_mode(){asserv_mode = ASSERV_MODE_ANGLE;}
void set_asserv_seq_mode(){asserv_mode = ASSERV_MODE_SEQUENCE;}

// obtenir les consignes en vitesse et vitesse angulaire
float get_cons_v(){return speed_asserv.speed_order_constrained.v;}
float get_cons_vt(){return speed_asserv.speed_order_constrained.vt;}

// observer les contraintes aux vitesse et vitesse angulaire
void constrain_speed(float v, float vt, float *v_constrained, float *vt_constrained){
    // contraintes
    float v_max = motionConstraint.v_max.v;
    float vt_max = motionConstraint.v_max.vt;
    float a_max = motionConstraint.a_max.a;
    float at_max = motionConstraint.a_max.at;
    float v_vt_max = motionConstraint.a_max.v_vt;
    float v_c_old = *v_constrained;

    // calcul des contraintes
    float period = DEFAULT_PERIOD;
    *v_constrained = limit_float(v,  *v_constrained-a_max*period,  *v_constrained+a_max*period);
    *v_constrained = limit_float(*v_constrained,-v_max,v_max);
    *vt_constrained = limit_float(vt,   *vt_constrained-at_max*period,   *vt_constrained+at_max*period);
    *vt_constrained = limit_float(*vt_constrained,-vt_max,vt_max);

    if (fabs((*v_constrained)*(*vt_constrained)) > v_vt_max){
        if (*v_constrained>0){
            *v_constrained = limit_float(
                    v_vt_max/fabs(*vt_constrained),
                    v_c_old-a_max*period,
                    v_c_old+a_max*period);
        }
        else {
            *v_constrained = limit_float(
                    -v_vt_max/fabs(*vt_constrained),
                    v_c_old-a_max*period,
                    v_c_old+a_max*period);
        }
    }
}

// contraindre les vitesses et accélérations autorisées
void constrain_speed_order(){

    // vitesse consigne(o comme order) et consigne contrainte(oc)
    float v_o = speed_asserv.speed_order.v;
    float vt_o = speed_asserv.speed_order.vt;
    float v_oc = speed_asserv.speed_order_constrained.v;
    float vt_oc = speed_asserv.speed_order_constrained.vt;

    constrain_speed(v_o, vt_o, &v_oc, &vt_oc);
    speed_asserv.speed_order_constrained.v = v_oc;
    speed_asserv.speed_order_constrained.vt = vt_oc;
}

// effectue un pas d'asservissement
void asserv_step(Odo *odo, float *commande_g, float *commande_d){
    // choix en fonction du mode d'asservissement (off, position ou vitesse)
    switch (asserv_mode){
        // si on est en roue libre
        case ASSERV_MODE_OFF :
            *commande_g = 0;
            *commande_d = 0;
            speed_asserv.speed_order_constrained = motionState.speed;
            break;
        // si on est en asservissement en position
        case ASSERV_MODE_POS :
            pos_asserv_step(odo, commande_g, commande_d);
            if (debug_mode){debug_pos_asserv();}
            break;
        // si on est en asservissement en vitesse
        case ASSERV_MODE_SPEED :
            if (debug_mode){debug_speed_asserv();}
            speed_asserv_step(odo, commande_g, commande_d);
            break;
        // si on est en asservissement en angle
        case ASSERV_MODE_ANGLE :
            //if (debug_mode){debug_speed_asserv();}
            angle_asserv_step(odo, commande_g, commande_d);
            break;
        case ASSERV_MODE_SEQUENCE :
            seq_asserv_step(odo, commande_g, commande_d);
            break;
    }
}

void speed_asserv_step(Odo *odo, float *commande_g, float *commande_d){
    // commandes des PID en delta et en alpha
    float commande_delta, commande_alpha;

    // vérifier qu'on est pas bloqué par un obstacle
    check_blocked(motionState.speed,speed_asserv.speed_order_constrained);
    // on commence par vérifier les contraintes de vitesses et accélération
    constrain_speed_order();
    // calcul des PID
    pid_set_order(&(speed_asserv.pid_delta), speed_asserv.speed_order_constrained.v);
    pid_set_order(&(speed_asserv.pid_alpha), speed_asserv.speed_order_constrained.vt);
    pid_maj(&(speed_asserv.pid_delta), odo->state->speed.v);
    pid_maj(&(speed_asserv.pid_alpha), odo->state->speed.vt);
    commande_delta = pid_process(&(speed_asserv.pid_delta));
    commande_alpha = pid_process(&(speed_asserv.pid_alpha));

    // renvoie des commandes gauche et droite
    *commande_g = commande_delta - commande_alpha;
    *commande_d = commande_delta + commande_alpha;

    /*
    // vérification si on est arrivé à la bonne consigne
    if (pid_done(speed_asserv.pid_delta) && pid_done(speed_asserv.pid_alpha)){
        speed_asserv.done = 1;
    } else {speed_asserv.done = 0;}
     */
}


void pos_asserv_step(Odo *odo, float *commande_g, float *commande_d){
    /*
     * On calcule les consignes de vitesse et vitesse angulaire
     * en fonction de la position actuelle et de la consigne de position.
     *
     * Idées :
     * La priorité à la rotation
     * on doit avoir une décroissance des consignes de vitesse plus lente que
     * celles autorisées par l'accélération max
     */
    // distance et angle restants à parcourir
    float x_o = pos_asserv.pos_order.x; // consigne en x
    float y_o = pos_asserv.pos_order.y; // consigne en y
    float x = odo->state->pos.x;
    float y = odo->state->pos.y;
    float d = sqrt((x_o-x)*(x_o-x) + (y_o-y)*(y_o-y));
    float dt = principal_angle(atan2f(y_o-y,x_o-x) - odo->state->pos.t);
    float v_o, vt_o, v_oc, vt_oc;
    float epsi = PI * 0.1;

    // si on est arrivé on ne bouge plus
    if (d < pos_asserv.stop_distance) {
        pos_asserv.done = 1;
        *commande_g = 0;
        *commande_d = 0;
    }
    else {
        // si |dt| > pi/2 , on calcul beta = dt-pi et c'est beta la nouvelle consigne
        // calcul de la consigne de vitesse et vitesse angulaire
        // on met en plus une sorte d'hysteresis pour éviter les aller-retour
        if (motionState.speed.v > 0){
            if (fabs(dt)>PI/2+epsi) {
                d = -d;
                dt = principal_angle(dt+PI);
            }
        } else {
            if (fabs(dt)>PI/2-epsi) {
                d = -d;
                dt = principal_angle(dt+PI);
            }
        }
        
        if (fabs(d)<0.1){
            v_o = pos_asserv.kp * d * (1-0.636619772*fabs(dt)); // 0.636619772 = 1/(pi/2)
            vt_o = pos_asserv.kp * 20 * dt * fabs(d);
        } else {
            v_o = pos_asserv.kp * d;
            vt_o = 2 * pos_asserv.kp * dt;
        }
        // appliquer les contraintes puis revérifier la priorité rotation
        // v_oc = speed_asserv.speed_order_constrained.v;
        // vt_oc = speed_asserv.speed_order_constrained.vt;
        // constrain_speed(v_o, vt_o, &v_oc, &vt_oc);
        //if (fabs(d)>0.1 && fabs(dt)>0.05){v_oc = 0.2*d*fabs(vt_oc/dt);} // si dt > 3°

        // appel de l'asserve en vitesse avec les bonnes consignes
        speed_asserv.speed_order.v = v_o;
        speed_asserv.speed_order.vt = vt_o;
        speed_asserv_step(odo,commande_g,commande_d);

        // mode debug
        if (debug_mode){
            pos_asserv.distance.d = d;
            pos_asserv.distance.dt = dt;
        }
    }
}

// asservissement en angle
void angle_asserv_step(Odo *odo, float *commande_g, float *commande_d){
    // angle restant à parcourir
    float dt = principal_angle(angle_asserv.angle_order - odo->state->pos.t);
    float vt_o;

    // si on est arrivé on ne bouge plus
    if (fabs(dt) < 0.02) {
        angle_asserv.done = 1;
        *commande_g = 0;
        *commande_d = 0;
    } else {
        // calcul de la vitesse angulaire nécessaire
        vt_o = 2 * dt;
        // appel de l'asserve en vitesse avec les bonnes consignes
        speed_asserv.speed_order.v = 0;
        speed_asserv.speed_order.vt = vt_o;
        speed_asserv_step(odo,commande_g,commande_d);
    }
}

// asservissement en sequence
void seq_asserv_step(Odo *odo, float *commande_g, float *commande_d){
    // si on est arrivé on ne bouge plus
    if (!(motionSequence.waiting)) {
        *commande_g = 0;
        *commande_d = 0;
    } else {
        // choix de la position en cours
        pos_asserv.pos_order = motionSequence.pos_seq[motionSequence.in_progress];
        pos_asserv.stop_distance = motionSequence.stop_distance[motionSequence.in_progress];
        pos_asserv_step(odo,commande_g,commande_d);
        // si cette étape est finie, passer à la suivante
        if (pos_asserv.done){
            pos_asserv.done = 0;
            motionSequence.waiting--;
            motionSequence.in_progress = !(motionSequence.in_progress);
        }
    }
}

// indique si l'asservissement en cours a terminé
int asserv_done(){
    if (asserv_mode == ASSERV_MODE_OFF) {return 1;}
    else if (asserv_mode == ASSERV_MODE_POS) {return pos_asserv.done;}
    else if (asserv_mode == ASSERV_MODE_SPEED) {return speed_asserv.done;}
    else if (asserv_mode == ASSERV_MODE_ANGLE) {return angle_asserv.done;}
    else if (asserv_mode == ASSERV_MODE_SEQUENCE) {return !(motionSequence.waiting);}
    else {return 0;}
}