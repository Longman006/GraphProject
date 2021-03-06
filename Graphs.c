/*
 * Graphs.c
 *
 *  Created on: 16.03.2017
 *      Author: longman
 */

#include "Graphs.h"

GRAPH* createGraph(GRAPH* graph,int n_nodes,int n_edges){


	NODE *nodes =(NODE*) malloc(n_nodes * sizeof(NODE));
	graph = (GRAPH*) malloc(sizeof(GRAPH));

	for(int i = 0 ; i < n_nodes ; i++){
		nodes[i].index=i;
		nodes[i].spin= i%2 ? 1:(-1);
		nodes[i].edges = (NODE**) malloc(n_edges * sizeof(NODE*));

		for(int j = 0 ; j < n_edges ; j++){
			nodes[i].edges[j] = NULL;
		}
	}

	graph->n_edges=n_edges;
	graph->n_nodes=n_nodes;
	graph->nodes=nodes;
	return graph;

}

void printGraph(GRAPH* graph){

	for(int i = 0 ; i< graph->n_nodes ; i++){
		printf("Wezel : %d Sasiedzi ",graph->nodes[i].index);
		for(int j = 0 ; j<graph->n_edges ; j++){
			printf(" %d ",graph->nodes[i].edges[j]->index);
		}
		printf("\n");
	}
}
void destroyGraph(GRAPH* graph){

	NODE* nodes = graph->nodes;

	for(int i = 0 ; i < graph->n_nodes ; i++){
		free(nodes[i].edges);
	}
	free(nodes);
	free(graph);
}
void connectGraph(GRAPH* graph){
	int n_nodes = graph->n_nodes;
	int n_edges = graph->n_edges;
	NODE* nodes = graph->nodes;

	int index = getRandom()%n_nodes; 	//index aktualnie obslugiwanego wezla
	int n_noEmptyEdge = 0;	//ile wezlow nie ma juz pustych krawedzi
	while(n_noEmptyEdge<n_nodes){

		printf("index : %d\n",index);
		NODE* currentNode = &nodes[index];
		int i = getEmptyEdgeIndex(currentNode,n_edges);

		if(i!=(-1)){
			int indexPair = getRandom()%n_nodes; 	// startowy numer wezla do porownania dla zwiekszenia losowosci
			for(int count = 0 ; count<n_nodes ; count++){

				NODE* nodeFound = &nodes[indexPair];
				int iPair = getEmptyEdgeIndex(nodeFound,n_edges);
				if(
						iPair>(-1) && 	//ma pusta galaz
						currentNode != nodeFound &&  	//nie jest samym soba
						!isEdge(currentNode,nodeFound,n_edges) 	// nie jest juz sasiadem
								 ){
					currentNode->edges[i]=nodeFound;
					nodeFound->edges[iPair]=currentNode;
					printf("Polaczenie : %d , %d \n",nodeFound->index,currentNode->index);
					break;
				}
				indexPair++;
				indexPair=indexPair%n_nodes;
			}
		}
		else {n_noEmptyEdge++;}
		index++;
		index=index%n_nodes;
	}
}

/**
 * Deprecated instead use fillSameSpins(g,SPIN_RANDOM)
 *
 */
void fillRandomSpins(GRAPH* graph)
{
    for(int i=0; i<graph->n_nodes; i++)
        graph->nodes[i].spin = getRandomSpin();
}
/**
 * Deprecated instead use fillSpins(g,SPIN_UP/DOWN)
 *
 */
void fillSameSpins(GRAPH* graph, SPIN spin)
{
	for(int i=0; i<graph->n_nodes; i++)
		graph->nodes[i].spin = spin;
}

void fillSpins(GRAPH* g,SPIN s){
	if(s == SPIN_RANDOM){
		fillRandomSpins(g);
	}
	else{
		fillSameSpins(g,s);
	}
}

void printGraphStats(GRAPH* graph)
{
    int spinUp = getSpinUpNum(graph);
    printf("Spins up: %d, spins down: %d\n", spinUp, graph->n_nodes - spinUp);
}

int getSpinUpNum(GRAPH* g)
{
    int sum = 0;
    for(int i=0; i<g->n_nodes; i++)
        if(g->nodes[i].spin == SPIN_UP)
            sum++;

    return sum;
}
int getSpinDownNum(GRAPH* g)
{
    return g->n_nodes - getSpinUpNum(g);
}
/**
 * TO samo tutaj , jak juz mamy SPIN_UP i DOWN to juz z niego korzystajmy
 * bedzie dwa razy mniej funkcji
 */

int getSpinNum(GRAPH* g,SPIN s){
	int sum = 0 ;
	for(int i =0 ; i< g->n_nodes ; i++){
		if(g->nodes[i].spin == s){
			sum++;
		}
	}
	return sum;
}
void setTemp(float T,GRAPH* g){
	g->temp = T;
	fprintf(stdout,"Temp set to : %f\n",g->temp);
}
