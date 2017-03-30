/*
 * Interface.h
 *
 *  Created on: 30.03.2017
 *      Author: longman
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_
#include "Graphs.h"
#include "Ising.h"
/**
 * UWAGA !!!
 * EXIT musi byc ostatni
 */
enum Options {SMALLSTEP=0,BIGSTEP,TIME_SPECTRUM,TEMP_SPECTRUM,SET_TEMP,EXIT};

void printMenu(void);
void testOptions(void);
const char* getOptionName(enum Options );

#endif /* INTERFACE_H_ */
