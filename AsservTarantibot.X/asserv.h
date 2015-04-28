#include "motion.h"
#ifndef _ASSERV_H_
#define _ASSERV_H_


typedef struct {
    float Ep; // erreur proportionnelle
    float Ei;//somme des erreurs
    float Ed; // dérivée de l'erreur

} Error;

typedef struct {
    float Kp; // erreur proportionnelle
    float Ki;//somme des erreurs
    float Kd; // dérivée de l'erreur
} PID;

void speed_asserv_step(Speed, Acceleration,float *,float*);
void asserv_init();
void init_rampe(Speed,Speed,Acceleration);
void rampe(Speed);

#endif
