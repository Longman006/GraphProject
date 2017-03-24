/*
 * Ising.h
 *
 *  Created on: 21.03.2017
 *      Author: maciekniewielki
 */
#ifndef ISING_H_
#define ISING_H_

#include "Graphs.h"
#include <math.h>

void applySmallMCStep(GRAPH*, float, float);
void applyBigMCStep(GRAPH*, float, float);
int calculateEnergyFromNeighbours(NODE*, int);
int _calculateContribution(NODE*, int);             //private
int calculateContributionDifference(NODE*, int);
float calculateSwitchProbability(int, float, float);

#endif // ISING_H_
