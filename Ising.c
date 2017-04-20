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

    int max = g->n_nodes - g->n_nodes/50;
    int min = g->n_nodes/50;
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
FILE* saveTempSpectrum(GRAPH * g,float TMin ,float TMax ,float deltaT,bool plot){

	char nazwa[100];

	sprintf(nazwa,"OdTempN%d",g->n_nodes);
	FILE* plik = fopen(nazwa,"w+");
	if(plik == NULL){
		fprintf(stdout,"Cannot open file %s\n",nazwa);
		return NULL;
	}
	for(float T = TMin ; T<TMax ; T+=deltaT){
		setTemp(T,g);
		for(int i=0; i<g->n_nodes; i++){
            nextStep(g);
		}
		fprintf(plik,"%f %f\n",T,getMagnetization(g));
	}
	rewind(plik);

	if(plot) {
		plotRawData(nazwa);
		fclose(plik);
		return NULL;
	}

	return plik;
}
FILE* saveTcSpectrum(int n_edges){

	int n_nodesMax = 100000;
	int n_nodesMin = 10;
	int multiplier=5;
	GRAPH* g;
	FILE* plik;
	float TMargin = 1;
	float TCritic = 2/log(n_edges/(n_edges-2));
	float TMin = ((TCritic<TMargin)?0:TCritic-TMargin) ;
	float TMax=TCritic +TMargin;
	float deltaT=0.1f;


	for(int n_nodes = n_nodesMin ; n_nodes<n_nodesMax ; n_nodes*=multiplier){
		g = getGraphFromPython(n_nodes,n_edges);
		plik=saveTempSpectrum(g,TMin,TMax,deltaT,false);

	}
	return plik;

}
float findTCritical(FILE* plik){
	float epsilon = 0.001f;
	float TCrit;
	float Temp;
	float magnetization;
	while(fscanf(plik,"%f %f",&Temp &magnetization) ){}
	return TCrit;
}

