/*
 * Statistics.c
 *
 *  Created on: 24.03.2017
 *      Author: maciekniewielki
 */

 #include "Statistics.h"

int getSpinUpNum(GRAPH* g)
{
    int sum = 0;
    for(int i=0; i<g->n_nodes; i++)
        if(g->nodes[i].spin == SPIN_UP)
            sum++;

    return sum;
}
int getSpinDownNum(GRAPH* g)
{
    return g->n_nodes - getSpinUpNum(g);
}
