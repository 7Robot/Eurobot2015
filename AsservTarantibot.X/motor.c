/* Device header file */
#include <xc.h>

#include "motor.h"
#include <math.h>
#include "user.h"
#include "lib_asserv/private/tools.h"

void Init_PWM(void)
{
    // P1TCON
    P1TCONbits.PTEN = 1;        // enable module PWM
    P1TCONbits.PTCKPS = 0;      // Clk input of the PWM module is TCY (no prescale)
    P1TCONbits.PTMOD = 0;       // free-runnig mode

    /*
     * la période des PWM (temps entre 2 fronts montants)
     * est fixée à 1500 cycles de 40MHz
     * ça donne une periode de sortie de 37.5 µs soit 26.66 kHz
     * RMQ : les registres de rapport cycliques ayant une précision double
     * leur valeur max sera 3000
     */
    P1TPER = 1500;

    //PWM1CON1
    PWM1CON1bits.PMOD2 = 1;     // sorties indépendantes
    PWM1CON1bits.PMOD3 = 1;
    // desactivation de toutes les sorties
    // à réactiver une fois le pinout trouvé ;)

    // sorties High du pwm
    // remapage au fil, on oublie la pin 2H (seem really dead, even in GPIO)
    PWM1CON1bits.PEN1H = 1; // sortie pwm
    PWM1CON1bits.PEN2H = 1; // sortie pwm
    PWM1CON1bits.PEN3H = 0;

    // sorties Low (opposé du High, on ne l'utilise pas)
    PWM1CON1bits.PEN1L = 0;
    PWM1CON1bits.PEN2L = 0;
    PWM1CON1bits.PEN3L = 0;

    P1TPER = 1500;

    P1DC1 = 0;// réglage des rapports cycliques, pour l'instant on mets 0 lors de l'initialisation
    P1DC2 = 0;

    MOTOR_BREAK1_tris = 0;
    MOTOR_BREAK2_tris = 0;
    MOTOR_DIR1_tris= 0;
    MOTOR_DIR2_tris = 0;
    // Activation en sortie des pin de sens du PONT en H
    MOTOR_BREAK1 = 0;
    MOTOR_BREAK2 = 0;
    MOTOR_DIR1= 0;
    MOTOR_DIR2 = 0;


}
/*
// QEI non utilis�s sur Bottox
void Init_QEI(void)
{
    // module QEI1 = Moteur Gauche
    QEI1CONbits.QEISIDL = 1;    // module toujours actif, meme en etat de pause du pic
    QEI1CONbits.QEIM = 6;       // module en mode x4 : regarde tous les fronts, reset sur index, désactivé en dessous
    QEI1CONbits.POSRES = 0;     // desactive l'index => pas de reset du compteur;
    QEI1CONbits.TQCS = 0;       // use PIC clock

    // configuration des pins A et B du module
    // ce sont des pins dites remapable,
    // ce qui veut dire que l'on peut choisir presque toutes les IO du PIC
    RPINR14bits.QEA1R = 24; // 25 = pin RP25
    RPINR14bits.QEB1R = 22;


    // module QEI2 identique = Moteur Droit
    QEI2CONbits.QEISIDL = 1;    // module toujours actif, meme en etat de pause du pic
    QEI2CONbits.QEIM = 6;       // module en mode x4 : regarde tous les fronts, reset sur index, désactivé en dessous
    QEI2CONbits.POSRES = 0;     // desactive l'index => pas de reset du compteur;
    QEI2CONbits.TQCS = 0;       // use PIC clock

    // configuration des pins A et B du module
    RPINR16bits.QEA2R = 23; // 23 = pin RP23
    RPINR16bits.QEB2R = 25;
}
*/

// Applique un PWM en ne réglant que les Duty-Cycle (compris entre -100 et 100)
// la fréquence du PWM est automatiquement réglée à 26.667 kHz (P1TPER=1500)
void PWM_Moteurs(float DC_gauche, float DC_droit)
{
    // variable temporaire servant a connaitre le signe des Duty-Cycle
    int DC_positif;

    // pins de sens du moteur gauche

    if (DC_droit >= 0) {
        MOTOR_DIR2 = 1;
    }
    else {
        MOTOR_DIR2 = 0;
    }

    if (DC_gauche >= 0) {
        MOTOR_DIR1 = 1;
    }
    else {
        MOTOR_DIR1 = 0;
    }



    // pins de sens du moteur droit
    DC_positif = (DC_gauche < 0);



    P1TPER = 1500;

    // limitation des Duty-Cycle
    DC_gauche = limit_float(DC_gauche,-DC_MAX,DC_MAX);
    DC_droit = limit_float(DC_droit,-DC_MAX,DC_MAX);

    // calcul des temps High des moteurs (cf datasheet)
    // RMQ : ici la précision est 2 fois plus grande que pour P1TPER
    P1DC1 =  (int) (30*fabs(DC_gauche));
    P1DC2 =  (int) (30*fabs(DC_droit));
}

// Applique un PWM en réglant la fréquence (1kHz-26.66kHz) et les Duty-Cycle (-100->+100)
void PWM_Moteurs_Detail(float frequence, float DC_gauche, float DC_droit)
{
    // variable temporaire servant a connaitre le signe des Duty-Cycle
    int DC_positif;

    // pins de sens du moteur gauche
    DC_positif = DC_droit >= 0;

    // pins de sens du moteur droit
    DC_positif = DC_gauche < 0;

    // calcul du nombre de cycles pour avoir la bonne fréquence (FCY/frequence)
    P1TPER = (int) limit_int((long int)(FCY/frequence),P1TPER_MIN,P1TPER_MAX);

    // limitation des Duty-Cycle
    DC_gauche = limit_float(DC_gauche,-100,100);
    DC_droit = limit_float(DC_droit,-100,100);

    DC_gauche = 2*P1TPER*fabs(DC_gauche)/100.0;
    DC_droit = 2*P1TPER*fabs(DC_droit)/100.0;

    // calcul des temps High des moteurs (cf datasheet)
    // RMQ : ici la précision est 2 fois plus grande que pour P1TPER
    P1DC1 = (int) limit_int((long int)(DC_gauche), 0, (long int)(2*P1TPER_MAX));
    P1DC2 = (int) limit_int((long int)(DC_droit), 0,  (long int)(2*P1TPER_MAX));
}

void PWM_Moteurs_gauche(float DC)
{
    // variable temporaire servant a connaitre le signe des Duty-Cycle
    int DC_positif;

    // pins de sens du moteur gauche
    DC_positif = (DC < 0); // => changer en fonction des sens des moteurs
    MOTOR_DIR1 = !DC_positif;


    // limitation des Duty-Cycle
    DC = limit_float(DC,-DC_MAX,DC_MAX);

    // calcul des temps High des moteurs (cf datasheet)
    // RMQ : ici la précision est 2 fois plus grande que pour P1TPER
    P1DC1 =  (int) (30*fabs(DC));
}

void PWM_Moteurs_droit(float DC)
{
    // variable temporaire servant a connaitre le signe des Duty-Cycle
    int DC_positif;

    // pins de sens du moteur droit
    DC_positif = (DC >= 0);
    MOTOR_DIR2 = !DC_positif;
    //MOTOR_1A_O = DC_positif;
    //MOTOR_1B_O = !DC_positif;
    
    //P1TPER = 1500;

    // limitation des Duty-Cycle
    DC = limit_float(DC,-DC_MAX,DC_MAX);

    // calcul des temps High des moteurs (cf datasheet)
    // RMQ : ici la précision est 2 fois plus grande que pour P1TPER
    P1DC2 =  (int) (30*fabs(DC));
}
