/*
 * File:   actions_ax12.h
 * Author: zoltarius
 *
 * Created on 4 avril 2014, 18:41
 */

#ifndef ACTIONS_AX12_H
#define	ACTIONS_AX12_H



#define rabd           7  // le rabateur
#define rabg          14  // le rabateur
#define pince          9  // la pince
#define asc           11 // l'ascenceur
#define tub            1    // le reservoir
#define clap           4
#define popcorn       17

void Init_ax12(void);
void charg_spot(void);
void charg_last_spot(void);
void release (void);
void close_claws(void);
void close_clap(void);
void open_clap(void);
void open_popcorn(void);
void close_popcorn(void);

#endif	/* ACTIONS_AX12_H */