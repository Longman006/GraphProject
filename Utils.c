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

float getRandom(void)
{
    return ((float)getRandom())/RAND_MAX;
}
