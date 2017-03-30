/*
 * Utils.h
 *
 *  Created on: 15.03.2017
 *      Author: longman
 */

#ifndef UTILS_H_
#define UTILS_H_
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<stdbool.h>

int getRandom(void);
int getRandomRange(int, int);
float getRandomFloat(void);
bool isSuccessful(float);
void plotRawData(char*);



#endif /* UTILS_H_ */
