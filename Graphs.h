/*
 * Graphs.h
 *
 *  Created on: 16.03.2017
 *      Author: longman
 */

#ifndef GRAPHS_H_
#define GRAPHS_H_
#include "Nodes.h"


struct Graph{
	int n_nodes;
	int n_edges;
	NODE *nodes;
	float temp;
};
typedef struct Graph GRAPH;


GRAPH* createGraph(GRAPH*,int,int);
void printGraph(GRAPH*);
void makeGraph(GRAPH*);
void destroyGraph(GRAPH*);
void connectGraph(GRAPH*);

void fillRandomSpins(GRAPH*);		//zbedne albo private
void fillSameSpins(GRAPH*, SPIN);	//zbedne albo private
void fillSpins(GRAPH*,SPIN);

void printGraphStats(GRAPH*);
int getSpinUpNum(GRAPH*); 			//zbedne
int getSpinDownNum(GRAPH*); 		//zbedne
int getSpinNum(GRAPH*,SPIN);

void setTemp(float ,GRAPH*);


#endif /* GRAPHS_H_ */
