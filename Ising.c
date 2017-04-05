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

float calculateSwitchProbability(int difference, float T)
{
    if(difference<=0)
        return 1.0f;
    else
        return exp(-difference/(KB * T));



}

void applySmallMCStep(GRAPH* g)
{
    int randIndex = getRandomRange(0, g->n_nodes);
    int energyDiff = calculateContributionDifference(&(g->nodes[randIndex]), g->n_edges);
    float probability = calculateSwitchProbability(energyDiff, g->temp);
    if(isSuccessful(probability))
        flipSpin(&(g->nodes[randIndex]));
}

void applyBigMCStep(GRAPH* g)
{

    for(int i=0; i<g->n_nodes; i++)
        applySmallMCStep(g);
}
int getStableSpinCount(GRAPH* g ){

	int epsilon = 10;
	int n_spinUp = 0;
	while(getSpinUpNum(g) - n_spinUp <epsilon){
		applyBigMCStep(g);
				n_spinUp = getSpinUpNum(g);
	}
	return n_spinUp;
}
float getMagnetization(GRAPH* g){
	int M = 0;
	for(int i = 0 ; i<g->n_nodes ; i++){
		M += g->nodes[i].spin;
	}
	return (float) M/g->n_nodes;
}
int nextStep(GRAPH* g ){
	float epsilon = 0.00001f;
	float M = getMagnetization(g);

	applyBigMCStep(g);
	if( fabs(getMagnetization(g) - M) > epsilon){
		return 1;
	}
	else return 0;
}
void saveTimeSpectrum(GRAPH* g){
	char nazwa[100];
	sprintf(nazwa,"OdCzasuT%fN%d",g->temp,g->n_nodes);
	FILE* plik = fopen(nazwa,"w+");
	if(plik == NULL){
		fprintf(stdout,"Cannot open file %s\n",nazwa);
		return ;
	}
	int i =0;
		while(nextStep(g) || i<1){ //takie reczne dowhile xD
			fprintf(plik,"%d %f\n",i,getMagnetization(g));
			i++;
		}
		rewind(plik);
		plotRawData(nazwa);
		fclose(plik);
}
void saveTempSpectrum(GRAPH * g){
	char nazwa[100];
	sprintf(nazwa,"OdTempN%d",g->n_nodes);
	FILE* plik = fopen(nazwa,"w+");
	if(plik == NULL){
		fprintf(stdout,"Cannot open file %s\n",nazwa);
		return ;
	}
	float deltaT = 0.005;
	float TMax = 4.5f;
	float epsilonT = 0.1;
	for(float T = 0 ; fabs(TMax - T) > epsilonT ; T+=deltaT){
		setTemp(T,g);
		while(nextStep(g)){}
		fprintf(plik,"%f %f\n",T,getMagnetization(g));
	}
	rewind(plik);
	plotRawData(nazwa);
	fclose(plik);
}
void setTemp(float T,GRAPH* g){
	fillRandomSpins(g);
	g->temp = T;
	fprintf(stdout,"Temp set to : %f\n",g->temp);
}
