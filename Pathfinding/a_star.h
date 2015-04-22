#ifndef a_star
#define a_star

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <queue>


class node
{

public:

	node(int x, int y, int h, int g);

    //Position du noeud
	int xPos;
	int yPos;

    //Coûts des déplacements
	int coutH;
	int coutG;

	int coutF;

    //Méthodes pour récupérer infos
    int get_xPos() const;
    int get_yPos() const;
    int get_coutG() const;
    int get_coutH() const;
    int get_coutF() const;

    //Méthodes de calculs de coûts
    int calculate_g(int direction); //Déplacement vers un noeud voisin
    int calculate_heuristic(node arrivee); //Heuristisue
    int modifyF(); //Coût total
};


class enemy
{

public:

	enemy(int x, int y, int rayon);

    //Position du noeud
	int xPos;
	int yPos;
	int rEnemy;

	int enemyNodes[51][51];

	void setEnemyNodes();
};

#endif
