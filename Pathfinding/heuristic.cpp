#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <queue>

#include "a_star.h"

using namespace std;


int heuristic_man(node n1, node n2)
{
	int xDist;
	int yDist;
	int hMan;

    xDist = abs(n2.xPos - n1.xPos);
    yDist = abs(n2.yPos - n1.yPos);

    hMan = xDist + yDist;

    return hMan;
}


float heuristic_euc(node n1, node n2)
{
	int xDist;
	int yDist;
	float hEuc;

    xDist = pow(abs(n2.xPos - n1.xPos),2);
    yDist = pow(abs(n2.yPos - n1.yPos),2);

    hEuc = sqrt(xDist + yDist);

    return hEuc;
}
