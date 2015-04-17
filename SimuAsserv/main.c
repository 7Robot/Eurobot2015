#include <stdio.h>
#include <stdlib.h>
#include "motion.h"
#include "odo.h"
#include "asserv.h"

void moteur(int*,int*,float*,float*);
FILE* fichier_v= NULL;
FILE* fichier_vt = NULL;

int main(void) {
    int tg=0,td=0,i= 0;
    float cg=0,cd=0;
    Speed test = {1,0};


    fichier_v = fopen("data_v.txt", "w+");
    fichier_vt = fopen("data_vt.txt", "w+");

    motion_init(); // initialisation odo,aserv
    motion_speed(test);
    for(i=0;i<2000;i++) {
        moteur(&tg,&td,&cg,&cd);
        motion_step(tg,td,&cg,&cd);
    }
    fclose(fichier_v);
    fclose(fichier_vt);
    return 0;
}

void moteur(int *tg,int *td,float *cg,float *cd) {// modélisation d'un moteur linéaire parfait E=kW
    *tg =*tg+(*cg);
    *td =*td+0.7*(*cd);

    printf("tics_g générés %d ; tics_d générés %d  \n",*tg,*td);
    printf("\n");
}
