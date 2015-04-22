#ifndef heuristic
#define heuristic

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <queue>

#include "a_star.h"


using namespace std;

int heuristic_man(node n1, node n2);

int heuristic_euc(node n1, node n2);


#endif
