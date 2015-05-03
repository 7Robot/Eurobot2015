#ifndef _ODO_H_
#define _ODO_H_

#include "motion.h"


/*****************************    Structures    *******************************/

// Coefficients de l'odométrie (relations tic/mètre et entraxe
typedef struct {
    int tic_by_meter;
    float meter_by_tic;
    float spacing;
} OdoCoefs;

// Enregistre les tics des encodeurs gauche et droit pour se repérer
typedef struct {
    int tics_g;
    int tics_d;
} OdoTics;

// Une odométrie constituée de coefs et associée à un état du robot
typedef struct {
    OdoCoefs coefs;
    OdoTics tics;
    MotionState *state;
    float period;
} Odo;



/******************************    Fonctions    *******************************/

// initialiser l'odométrie
void odo_init();

// assigner des valeurs aux coefs (relations tic/mètre et entraxe)
void odo_set_coefs (Odo *odo, OdoCoefs coefs);
void odo_set_tic_by_meter(Odo *odo, int tic_by_meter);
void odo_set_spacing(Odo *odo, float spacing);

// lier l'odométrie à un état du robot (positions, vitesses, ...)
void odo_set_state(Odo *odo, MotionState *state);

// indiquer la période entre 2 mesures pour l'odométrie
void odo_set_period(Odo *odo, float period);

// MAJ de l'état du robot avec les valeurs des QEI gauche et droit
void odo_step(Odo *odo, int qei_g, int qei_d);

#endif // _ODO_H_