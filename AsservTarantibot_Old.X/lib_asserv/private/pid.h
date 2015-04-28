#ifndef _PID_H_
#define _PID_H_


/*****************************    Structures    *******************************/

// Coefficients du PID (proportionnel, integrale, derivée) et leurs coefs de moyennage
typedef struct {
    float kp;
    float ki;
    float kd;
    float mu_p;
    float mu_d;
} PidCoefs;

// Etat des valeurs du PID (erreur, intégrale de l'erreur, dérivée de l'erreur) et borne de l'intégrale
typedef struct {
    float err;
    float err_moy; // erreur moyennee
    float err_int;
    float err_der;
    float err_der_moy; // derivee moyennee
    float max_int;
} PidState;

// Valeurs de l'erreur et de sa dérivée permettant de considérer que le robot est arrivé
typedef struct {
    float err_eps;
    float der_eps;
} PidEps;

// Un PID est constitué de coefs, de valeurs d'état et d'une consigne
typedef struct {
    PidCoefs coefs;
    PidState state;
    PidEps eps;
    float order;
} Pid;



/******************************    Fonctions    *******************************/

// assigner des valeurs aux coefs
void pid_set_coefs(Pid *pid, PidCoefs coefs);
void pid_set_kp(Pid *pid, float kp);
void pid_set_ki(Pid *pid, float ki);
void pid_set_kd(Pid *pid, float kd);
void pid_set_mu_p(Pid *pid, float mu_p);
void pid_set_mu_d(Pid *pid, float mu_d);

// assigner des valeurs à l'état du PID
void pid_set_state(Pid *pid, PidState state);
void pid_set_err(Pid *pid, float err);
void pid_set_err_int(Pid *pid, float err_int);
void pid_set_err_der(Pid *pid, float err_der);
void pid_set_max_int(Pid *pid, float max_int);

// assigner des valeurs aux erreur et derivée permettant de considérer que le robot est arrivé
void pid_set_eps(Pid *pid, PidEps eps);
void pid_set_eps_err(Pid *pid, float err);
void pid_set_eps_der(Pid *pid, float der);

// remise à zero de l'intégrale du PID
void pid_reset(Pid *pid);
// assigner une valeur de consigne
void pid_set_order(Pid *pid, float order);

// maj de l'état du PID
void pid_maj(Pid *pid, float value);
void pid_maj_err(Pid *pid, float value);
void pid_maj_err_int(Pid *pid, float err);
void pid_maj_err_der(Pid *pid, float err_old);

// calcule la commande du PID
float pid_process(Pid *pid);

// indique si le pid a terminé
int pid_done(Pid pid);


#endif // _PID_H_