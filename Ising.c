/*
 * Ising.c
 *
 *  Created on: 21.03.2017
 *      Author: maciekniewielki
 */
 /*This file provides the Ising model functions*/

 #include "Ising.h"

int calculateEnergyFromNeighbours(Node* node, int n_edges)
{
    int sum = 0;
    for(int i=0; i<n_edges; i++)
        sum +=node->spin * node->edges[i]->spin;

    return -sum;
}
