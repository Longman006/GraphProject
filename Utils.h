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
#include<math.h>

int getRandom(void);
int getRandomRange(int, int);
float getRandomFloat(void);
bool isSuccessful(float);
void plotRawData(char*);
float nonlinearNormalize(float,float,float,float,float ,bool);
float linearNormalize(float,float,float,float,float ,bool);
float expInverseNorm(float,float,float,float,float);


#endif /* UTILS_H_ */
