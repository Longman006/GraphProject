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
	TIME_SPECTRUM=0,
	SET_TMIN,
	SET_TMAX,
	SET_DELTAT,
	SET_TEMP,
	SET_SPINS,
	SET_N_NODES,
	SET_N_EDGES,
	CREATE_GRAPH,
	TEMP_SPECTRUM,
	TC_N_NODES,
	EXIT};

SPIN getSpinSelect(void);
int getNSelect(enum Options );
void printMenu(void);
const char* getOptionName(enum Options );
float getXSelect(enum Options );
#endif /* INTERFACE_H_ */
