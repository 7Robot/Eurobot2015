#ifndef _DEBUG_H_
#define _DEBUG_H_

#define DEBUG_COUNT_MAX 800

// pour le réglage de l'asserv (tableaux à récupérer en mode debug)
typedef struct {
    // consignes en vitesse et vitesse angulaire du robot
    float v[DEBUG_COUNT_MAX];
    float vt[DEBUG_COUNT_MAX];
    float cons_v[DEBUG_COUNT_MAX];
    float cons_vt[DEBUG_COUNT_MAX];
} SpeedDebug;

// pour le réglage de l'asserv (tableaux à récupérer en mode debug)
typedef struct {
    float d[DEBUG_COUNT_MAX];
    float dt[DEBUG_COUNT_MAX];
    float cons_v[DEBUG_COUNT_MAX];
    float cons_vt[DEBUG_COUNT_MAX];
} PosDebug;

/*#############################    Fonctions    ##############################*/

void set_debug_mode(int mode);
void debug_init();
void debug_speed_asserv();
void debug_pos_asserv();


#endif // _DEBUG_H_