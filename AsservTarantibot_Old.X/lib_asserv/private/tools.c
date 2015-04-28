#include "tools.h"
#include <math.h>

// Renvoyer une valeur comprise entre inf et sup
float limit_float(float valeur, float inf, float sup){
    if (valeur < inf) return inf;
    else if (valeur > sup) return sup;
    else return valeur;
}

long int limit_int(long int valeur, long int inf, long int sup){
    if (valeur < inf) return inf;
    else if (valeur > sup) return sup;
    else return valeur;
}

// angle principal
float principal_angle(float angle){
    float alpha;
    if (fabs(angle)< PI){return angle;}
    else {
        alpha = fmod(angle,2*PI);
        if (alpha<-PI){alpha += 2*PI;} // décalage de 2PI remarqué par Ken si l'angle est négatif
        if (alpha>PI){alpha -= 2*PI;}
        return alpha;
    }
}
