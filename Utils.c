/*
 * Utils.c
 *
 *  Created on: 15.03.2017
 *      Author: longman
 */
#include "Utils.h"


void plotRawData(char* dane){
	char komenda[100];
	FILE* gnuplotPipe = popen("gnuplot -persistent","w");
	if(!gnuplotPipe){
		fprintf(stdout,"Could not open pipe : %s\n",dane);
		return;
	}
	sprintf(komenda,"plot '%s' using 1:2\n",dane);
	fprintf(gnuplotPipe, "%s\n",komenda);
	fflush(gnuplotPipe);
	pclose(gnuplotPipe);
}
int getRandom(void){
	static int check = 0;
	if(!check){
		check =1;
		srand(time(NULL));
	}
	return rand();
}

int getRandomRange(int min, int max)
{
    int diff = max - min;
    int rnd = getRandom();

    return (rnd % diff) + min;
}

float getRandomFloat(void)
{
    return ((float)getRandom())/RAND_MAX;
}

bool isSuccessful(float probability)
{
    return getRandomFloat()<probability;
}

