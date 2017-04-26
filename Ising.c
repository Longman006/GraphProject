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
float calculateTCritical(int n_edges){
	return 2/logf((float)n_edges/(n_edges-2));
}
void plotCriticalTemp(void){
	char nazwa[100];
	sprintf(nazwa,"TempKrytycznaOdK");
	FILE* plik = fopen(nazwa,"w+");
	if(plik == NULL){
		fprintf(stdout,"Cannot open file %s\n",nazwa);
		return;
	}
	for(int K = 2 ; K<20 ; K++){
		fprintf(plik,"%d %f\n",K,calculateTCritical(K));
	}
	rewind(plik);
	plotRawData(nazwa);
	fclose(plik);
}
FILE* saveTcSpectrum(int n_edges,SPIN s,bool plot){

	GRAPH* g;
	FILE* plikTemp;
	char nazwa[100];
	sprintf(nazwa,"TempKrytycznaK%d",n_edges);
	FILE* plik = fopen(nazwa,"w+");

	if(plik == NULL){
		fprintf(stdout,"Cannot open file %s\n",nazwa);
		return NULL;
	}

	float TCritic = calculateTCritical(n_edges);
	printf("TCritical : %f\n",TCritic);

	int n_nodesMax = 100000;
	int n_nodesMin = 20;
	int n_nodesRange = n_nodesMax-n_nodesMin;
	int n_nodesCenter = n_nodesMin+n_nodesRange/1000;

	float TMargin=0;
	float TMarginMin=0.2f;
	float TMarginMax=6.0f;

	float TMin=0;
	float TMax=0;

	float deltaT=0;
	float deltaTMax = 0.5f;
	float deltaTMin = 0.03f; //mozna poprawic w razie potrzeby

	int multiplier=4.0;
	float TFound=0;

	for(int n_nodes = n_nodesMin ; n_nodes<n_nodesMax ; n_nodes*=multiplier){
		printf("n_nodes : %d\n",n_nodes);
		TMargin = expInverseNorm(
				n_nodes,
				TMarginMax,
				TMarginMin,
				n_nodesMin,
				n_nodesMax
				);
		//printf("TMargin : %f\n",TMargin);
		TMin = ((TCritic<TMargin)?0:TCritic-TMargin/2);
		TMax = TCritic +TMargin;

		deltaT = expInverseNorm(
				n_nodes,
				deltaTMax,
				deltaTMin,
				n_nodesMin,
				n_nodesMax
				);
		//printf("TDelta : %f\n",deltaT);

		g = getGraphFromPython(n_nodes,n_edges);
		fillSpins(g,s);
		plikTemp=saveTempSpectrum(g,TMin,TMax,deltaT,false);
		TFound = findTCritical(plikTemp);

		printf("TFound : %f\n",TFound);
		fprintf(plik,"%f %f\n",(float)1/n_nodes,TFound);
		fclose(plikTemp);
	}
	rewind(plik);
	if(plot) {
		plotRawData(nazwa);
		fclose(plik);
		return NULL;
	}
	return plik;

}
float findTCritical(FILE* plik){
	float epsilonT = 0.08f;
	float epsilon = 0.08f;
	float Temp;
	float prevTemp=0;
	float prevMagnetization =10;
	float magnetization;
	while(fscanf(plik,"%f %f\n",&Temp ,&magnetization)==2 ){
		if(fabs(prevMagnetization -magnetization)<epsilon){
			if(fabs(magnetization)<epsilonT){
				break;
			}
		}
		//printf("prev : %f\n",prevMagnetization);
		//printf("magnet : %f\n",magnetization);
		//printf("Temp : %f\n",Temp);
		prevMagnetization=magnetization;
		prevTemp = Temp;
	}
	return prevTemp;///albo return prevTemp nie jestem pewien
}

