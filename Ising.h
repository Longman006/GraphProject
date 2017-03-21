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

int calculateEnergyFromNeighbours(Node*, int);
int _calculateContribution(Node*, int);             //private
int calculateContributionDifference(Node*, int);
float calculateSwitchProbability(int, float);

#endif // ISING_H_
