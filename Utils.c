/*
 * Utils.c
 *
 *  Created on: 15.03.2017
 *      Author: longman
 */
#include "Utils.h"

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

SPIN getRandomSpin(void)
{
    if(getRandom()%2 == 1)
        return SPIN_UP;
    else
        return SPIN_DOWN;
}
