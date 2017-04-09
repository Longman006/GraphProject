/*
 * Nodes.h
 *
 *  Created on: 15.03.2017
 *      Author: longman
 */

#ifndef NODES_H_
#define NODES_H_

#define SPIN_UP 1
#define SPIN_DOWN -1
#define SPIN_RANDOM 0
typedef signed char SPIN;

#include "Utils.h"


struct Node{
	int index;
	SPIN spin;
	struct Node **edges;
};

typedef struct Node NODE;

SPIN getRandomSpin(void);
void flipSpin(NODE*);
void destroyNodes(NODE**,int);
int getEmptyEdgeIndex(NODE*,int);
int isEdge(NODE*,NODE*,int);
//NODE* findPair(GRAPH,NODE*, int,int);
#endif /* NODES_H_ */
