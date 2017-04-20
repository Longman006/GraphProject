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
#include "parseGraph.h"

//Zwykly Ising od czasu
void applySmallMCStep(GRAPH*);
void applyBigMCStep(GRAPH*);
int calculateEnergyDifference(NODE*, int);
float calculateSwitchProbability(int, float);
float getMagnetization(GRAPH* g);
void saveTimeSpectrum( GRAPH* );

//OD temperatury
FILE* saveTempSpectrum(GRAPH* ,float,float,float,bool);
int getStableSpinCount(GRAPH* );
FILE* saveTcSpectrum(int );
int nextStep(GRAPH* );
float findTCritical(FILE*);
#endif // ISING_H_
