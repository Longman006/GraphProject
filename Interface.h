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
enum Options {
	SMALLSTEP=0,
	BIGSTEP,
	TIME_SPECTRUM,
	TEMP_SPECTRUM,
	SET_TEMP,
	SET_SPINS,
	SET_N_NODES,
	SET_N_EDGES,
	CREATE_GRAPH,
	EXIT};

SPIN getSpinSelect(void);
int getNSelect(enum Options o);
void printMenu(void);
void testOptions(void);
const char* getOptionName(enum Options );
float getTempSelect(void);
#endif /* INTERFACE_H_ */
