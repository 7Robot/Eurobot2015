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
#define asc            11 // l'ascenceur
#define tub            1    // le reservoir
#define clapl          4    // old clap
#define clapr          22
#define popcorn_d           17
#define popcorn_g           20

// CLLC
// CLRO

#define NUM_ACTIONS_BUFFER 20


void Add_Action_AX12(char Action_ToDo);
void Faire_Actions_AX12(void);

#define AX12_INIT_AX12           1
void Init_ax12(void);
#define AX12_CHARG_SPOT          2
void charg_spot(void);
#define AX12_CHARG_LAST_SPOT     3
void charg_last_spot(void);
#define AX12_RELEASE             4
void release (void);
#define AX12_CLOSE_CLAWS         5
void close_claws(void);
#define AX12_OPEN_CLAWS          6
void open_claws(void);
#define AX12_OPEN_POPCORN_D      9
void open_popcorn_d(void);
#define AX12_CLOSE_POPCORN_D     10
void close_popcorn_d(void);
#define AX12_CLOSE_TUB           11 //CLTB asynchrone
void close_tub(void);            
#define AX12_CLOSE_CLAPR         12
void close_clap_r(void);
#define AX12_OPEN_CLAPR          13
void open_clap_r(void);
#define AX12_CLOSE_CLAPL         14
void close_clap_l(void);
#define AX12_OPEN_CLAPL          15
void open_clap_l(void);
#define AX12_OPEN_POPCORN_G      16
void open_popcorn_g(void);
#define AX12_CLOSE_POPCORN_G     17
void close_popcorn_g(void);

#endif	/* ACTIONS_AX12_H */