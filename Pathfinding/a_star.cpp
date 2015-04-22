// A* Algorithm - 7Robot

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <queue>

#include "a_star.h"
#include "heuristic.h"

using namespace std;

node::node(int x, int y, int h, int g)
{
    xPos = x;
    yPos = y;
    coutH = h;
    coutG = g;
}

int node::get_xPos() const
{
    return xPos;
}

int node::get_yPos() const
{
    return yPos;
}

int node::get_coutG() const
{
    return coutG;
}

int node::get_coutH() const
{
    return coutH;
}

int node::get_coutF() const
{
    return coutF;
}

int node::calculate_heuristic(node arrivee)
{
    this->coutH = heuristic_man(*this, arrivee);
}

int node::calculate_g(int direction)
{
    if(direction%2 == 0)
    {
        this->coutG += 2;
    }

    else
    {
        this->coutG += 3;
    }
}

int node::modifyF()
{
    this -> coutF = this -> coutG + this -> coutH;
}



enemy::enemy(int x, int y, int rayon)
{
    xPos = x;
    yPos = y;
    rEnemy = rayon;

    setEnemyNodes();
}

void enemy::setEnemyNodes()
{
    int i;
    int j;


    for(i =0; i <51; i++)
    {
        for(j =0; j <51; j++)
        {
            if((this->rEnemy)==0)
            {
            this->enemyNodes[i][j]=0;
            }

            else if((i-25)*(i-25) + (j-25)*(j-25) <= (this->rEnemy)*(this->rEnemy))
            {
                this->enemyNodes[i][j]=1;
            }

            else
            {
                this->enemyNodes[i][j]=0;
            }

        }

    }
}
