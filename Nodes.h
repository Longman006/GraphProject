/*
 * Nodes.h
 *
 *  Created on: 15.03.2017
 *      Author: longman
 */

#ifndef NODES_H_
#define NODES_H_
#include "Utils.h"


#define SPIN_UP 1
#define SPIN_DOWN -1
typedef signed char SPIN;

struct Node{
	int index;
	SPIN spin;
	struct Node **edges;
};

typedef struct Node NODE;


void flipSpin(NODE*);
void destroyNodes(NODE**,int);
int getEmptyEdgeIndex(NODE*,int);
int isEdge(NODE*,NODE*,int);
//NODE* findPair(GRAPH,NODE*, int,int);
#endif /* NODES_H_ */
