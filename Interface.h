/*
 * Interface.h
 *
 *  Created on: 30.03.2017
 *      Author: longman
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_
#include<stdio.h>
#include "Nodes.h"
/**
 * UWAGA !!!
 * EXIT musi byc ostatni
 */
enum Options {SMALLSTEP=0,BIGSTEP,TIME_SPECTRUM,TEMP_SPECTRUM,SET_TEMP,SET_SPINS,EXIT};

SPIN getSpinSelect(void);
void printMenu(void);
void testOptions(void);
const char* getOptionName(enum Options );

#endif /* INTERFACE_H_ */
