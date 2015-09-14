/*
 * File:   actions_ax12.h
 * Author: zoltarius
 *
 * Created on 4 avril 2014, 18:41
 */

#ifndef ACTIONS_AX12_H
#define	ACTIONS_AX12_H



#define socle           42  // La fixation du bras droit sur le robot
#define haut            12  // l'Ax-12 suivant : en haut du "levier"
#define verseur_d       6   // L'actionneur de la plaque suppérieur droite
#define verseur_g       16  // L'actionneur de la plaque suppérieur gauche
#define pince_d         2   // L'actionneur de la plaque inférieur droite
#define pince_g         10  // L'actionneur de la plaque inférieur gauche
#define coude           13  // L'ax-12 permettant de ranger le bras gauche

void choose_arm(int);
void init_ax12(void);
void deploy(void);
void lacher(void);
void ranger(void);
void victory_dance (void);

#endif	/* ACTIONS_AX12_H */