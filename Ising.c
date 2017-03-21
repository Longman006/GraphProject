/*
 * Ising.c
 *
 *  Created on: 21.03.2017
 *      Author: maciekniewielki
 */
 /*This file provides the Ising model functions*/

 #include "Ising.h"

int calculateEnergyFromNeighbours(NODE* node, int n_edges)
{
    int sum = 0;
    for(int i=0; i<n_edges; i++)
        sum +=node->spin * node->edges[i]->spin;

    return -sum;
}

int calculateContributionDifference(NODE* node, int n_edges)
{
    int energy = 0, flippedEnergy = 0;

    energy = _calculateContribution(node, n_edges);
    flipSpin(node);
    flippedEnergy = _calculateContribution(node, n_edges);
    flipSpin(node);

    return flippedEnergy - energy;
}

int _calculateContribution(NODE* node, int n_edges)
{
    int energy = calculateEnergyFromNeighbours(node, n_edges);
    for(int i=0; i<n_edges; i++)
        energy += calculateEnergyFromNeighbours(node->edges[i], n_edges);

    return energy;
}

float calculateSwitchProbability(int difference, float kb = 1)
{
    if(difference<=0)
        return 1.0f;
    else
        return exp(-difference * kb);
}


