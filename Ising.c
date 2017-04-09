/*
 * Ising.c
 *
 *  Created on: 21.03.2017
 *      Author: maciekniewielki
 */
 /*This file provides the Ising model functions*/

 #include "Ising.h"

int calculateEnergyDifference(NODE* node, int n_edges)
{
    int sum = 0;
    for(int i=0; i<n_edges; i++)
        sum += node->edges[i]->spin;

    int energy = 2*node->spin*sum;

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
    int energyDiff = calculateEnergyDifference(&(g->nodes[randIndex]), g->n_edges);
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
	return fabs(((float) M)/g->n_nodes);
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
	sprintf(nazwa,"OdCzasuT%fN%d.txt",g->temp,g->n_nodes);
	FILE* plik = fopen(nazwa,"w+");
	if(plik == NULL){
		fprintf(stdout,"Cannot open file %s\n",nazwa);
		return ;
	}
	/*
	int i =0;
		while(nextStep(g) || i<1){ //takie reczne dowhile xD
			fprintf(plik,"%d %f\n",i,getMagnetization(g));
			i++;
		}*/
    int max = g->n_nodes - g->n_nodes/50;
    int min = g->n_nodes - min;
    int iterationEnd = g->n_nodes/20;
    for(int i=0; i<iterationEnd; i++)
    {
        nextStep(g);
        fprintf(plik,"%d %f\n",i,getMagnetization(g));
        int spinsUp = getSpinUpNum(g);
        if((spinsUp<min || spinsUp>max)&&i>iterationEnd/10)
            break;
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
	float deltaT = 0.5;
	float TMax = 5.0f;
	float epsilonT = 0.1;
	for(float T = 0.0f ; fabs(TMax - T) > epsilonT ; T+=deltaT){
		setTemp(T,g);
		for(int i=0; i<g->n_nodes; i++){
            nextStep(g);
		}
		fprintf(plik,"%f %f\n",T,getMagnetization(g));
	}
	rewind(plik);
	plotRawData(nazwa);
	fclose(plik);
}

