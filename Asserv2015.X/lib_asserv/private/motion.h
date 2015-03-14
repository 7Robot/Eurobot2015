#ifndef _MOTION_H_
#define _MOTION_H_


/*****************************    Structures    *******************************/

// Position absolue du robot (x, y, et theta)
typedef struct {
    float x; // en mètre
    float y; // en mètre
    float t; // en radian
} Position;

// Vitesse et vitesse angulaire du robot
typedef struct {
    float v; // en m/s
    float vt; // en rad/s
} Speed;

// accélération du robot (dv/dt,  d2theta/dt2   et   v*(dtheta/dt))
typedef struct {
    float a; // en m/s2
    float at; // en rad/s2
    float v_vt; // en rad*m/s2
} Acceleration;

// état du robot (position, vitesse et accélération)
typedef struct {
    Position pos;
    Speed speed;
    Acceleration acc;
} MotionState;

// contraintes de déplacement du robot (sur les vitesses et accélérations max)
typedef struct {
    Speed v_max;
    Acceleration a_max;
} MotionConstraint;

// sequence de 2 consignes en position
typedef struct {
    Position pos_seq[2];
    float stop_distance[2];
    int in_progress; // 0 ou 1 suivant la position en cours
    int waiting; // 0, 1, ou 2 si un ordre en attente
} MotionSequence;


/******************************    Fonctions    *******************************/

// initialiser la lib d'asservissement
void motion_init(void(*_done)(void));

// assigner des valeurs à la position (x, y et theta)
void set_position(Position pos);
void set_position_x(MotionState *state, float x);
void set_position_y(MotionState *state, float y);
void set_position_t(MotionState *state, float t);

// assigner des valeurs à la vitesse (vitesse et vitesse angulaire)
void set_speed(MotionState *state, Speed speed);
void set_speed_v(MotionState *state, float v); // vitesse
void set_speed_vt(MotionState *state, float vt); // vitesse angulaire

// assigner des valeurs à l'accélération
void set_acceleration(MotionState *state, Acceleration acc);
void set_acceleration_a(MotionState *state, float a); // accélération
void set_acceleration_at(MotionState *state, float at); // accélération angulaire
void set_acceleration_v_vt(MotionState *state, float v_vt); // vitesse * vitesse angulaire

// connaître l'état du robot
Position get_position();
Speed get_speed();
Acceleration get_acceleration();

// obtenir les vitesses des roues gauche et droite
float get_vg();
float get_vd();

// consignes de déplacements du robot
void motion_free(); // passer en roue libre
void motion_pos(Position pos); // aller à cette position
void motion_sequence(Position pos1, Position pos2); // sequence de 2 positions
void motion_push(Position pos, float stop_distance); // ajoute ou remplace le prochain ordre de la sequence
void motion_speed(Speed speed); // avancer à cette vitesse
void motion_angle(float abs_angle); // tourner pour être à un angle (absolu) alpha

// checker si le déplacement est terminé
int motion_done();

// vérifier qu'on est pas bloqué par un obstacle
void check_blocked(Speed speed,Speed order);

// renvoie les commandes des roues gauche et droite (appelé par l'interruption toutes les 5 ms)
void motion_step(int tics_g, int tics_d, float *commande_g, float *commande_d);


#endif // _MOTION_H_