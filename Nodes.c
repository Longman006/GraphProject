/*
 * Nodes.c
 *
 *  Created on: 15.03.2017
 *      Author: longman
 */
#include "Nodes.h"


/*
 * Returns -1 if no empty edge is found
 *
 */
int  getEmptyEdgeIndex(NODE* node, int n_edges){
	for(int j = 0 ; j<n_edges ; j++){
		NODE* currentEdge = node->edges[j];
			if(!currentEdge){
				return j;
			}
	}
	return -1;
}
int isEdge(NODE* node,NODE* compare,int n_edges){
	for(int i = 0; i<n_edges ; i++){
		if(node->edges[i] == compare){
			return 1;
		}
	}
	return 0;
}

void flipSpin(NODE* node)
{
    if(node->spin == SPIN_UP)
        node->spin = SPIN_DOWN;
    else
        node->spin = SPIN_UP;
}

