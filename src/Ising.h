/*
 * Ising.h
 *
 *  Created on: 21.03.2017
 *      Author: maciekniewielki
 */
#ifndef ISING_H_
#define ISING_H_
#define KB 1

#include "Graphs.h"
#include <math.h>
#include "Statistics.h"

//Zwykly Ising od czasu
void applySmallMCStep(GRAPH*);
void applyBigMCStep(GRAPH*);
int calculateEnergyFromNeighbours(NODE*, int);
int _calculateContribution(NODE*, int);             //private
int calculateContributionDifference(NODE*, int);
float calculateSwitchProbability(int, float);
float getMagnetization(GRAPH* g);

//OD temperatury
void setTemp(float ,GRAPH*);
void saveTempSpectrum(GRAPH* );
int getStableSpinCount(GRAPH* );
void saveTimeSpectrum( GRAPH* );
int nextStep(GRAPH* );
#endif // ISING_H_
