/*
 * File:   actions_ax12.h
 * Author: zoltarius
 *
 * Created on 4 avril 2014, 18:41
 */

#ifndef ACTIONS_AX12_H
#define	ACTIONS_AX12_H



#define rabd           7  // le rabateur
#define rabg           14  // le rabateur
#define pince          9  // la pince
#define asc           11 // l'ascenceur
#define tub            1    // le reservoir

void choose_arm(int);
void Init_ax12(void);
void charg_spot(void);

#endif	/* ACTIONS_AX12_H */