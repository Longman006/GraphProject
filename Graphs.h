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
};
typedef struct Graph GRAPH;


GRAPH* createGraph(GRAPH*,int,int);
void printGraph(GRAPH*);
void makeGraph(GRAPH*);

#endif /* GRAPHS_H_ */
