#ifndef _CONFIG_H_
#define _CONFIG_H_

// Dossier contenant les valeurs retenus pour l'asservissement
#define NULL 0
#define DEFAULT_CONSTRAINT_V_MAX 0.45
#define DEFAULT_CONSTRAINT_VT_MAX 0.7
#define DEFAULT_CONSTRAINT_A_MAX 0.1
#define DEFAULT_CONSTRAINT_AT_MAX 0.2
#define DEFAULT_CONSTRAINT_VT_T_MAX 0.10

#define speed_threshold 0.05 // A ajuster au systeme, attention a ne pas etre trop greedy

// Define Odométrie
#define DEFAULT_PERIOD 0.005 // période de rafraichissement de l'asserv
#define tic_by_meter 1000 // a adapter
#define meter_by_tic 0.001 // a adapter
#define spacing 0.2732 // en m a adapter
#define period 0.005
#define DEFAULT_STOP_DISTANCE 0.01
#define PI 3.1415


#endif //fin
