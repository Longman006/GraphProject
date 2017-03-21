/*
 * Ising.h
 *
 *  Created on: 21.03.2017
 *      Author: maciekniewielki
 */
#ifndef ISING_H_
#define ISING_H_

#include "Nodes.h"
#include <math.h>

int calculateEnergyFromNeighbours(NODE*, int);
int _calculateContribution(NODE*, int);             //private
int calculateContributionDifference(NODE*, int);
float calculateSwitchProbability(int, float);

#endif // ISING_H_
