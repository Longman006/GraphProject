/*
 * Nodes.h
 *
 *  Created on: 15.03.2017
 *      Author: longman
 */

#ifndef NODES_H_
#define NODES_H_
#include "Utils.h"



typedef char SPIN;

struct Node{
	int index;
	SPIN spin;
	struct Node **edges;
};

typedef struct Node NODE;



void destroyNodes(NODE**,int);
int getEmptyEdgeIndex(NODE*,int);
int isEdge(NODE*,NODE*,int);
//NODE* findPair(GRAPH,NODE*, int,int);
#endif /* NODES_H_ */
