#include "parseGraph.h"
#include <stdlib.h>
GRAPH* allocateGraph(int n_nodes,int n_edges){

	GRAPH* g = (GRAPH*)malloc(sizeof(GRAPH));
	g->n_edges = n_edges;
	g->n_nodes = n_nodes;
	g->nodes = (NODE*)malloc(sizeof(NODE)*g->n_nodes);
	for(int i=0; i<g->n_nodes; i++){
		g->nodes[i].index = i;
		g->nodes[i].edges = (NODE**)malloc(sizeof(NODE*)*g->n_edges);
	}
	return g;

}
GRAPH* getGraph(FILE* file)
{

    int n_edges;
    int n_nodes;
    fscanf(file, "%d%d", &n_nodes, &n_edges);
    GRAPH* g = allocateGraph(n_nodes,n_edges);

    for(int i=0; i<g->n_nodes; i++)
    {
        int currentNumber;
        fscanf(file, "%d", &currentNumber);
        for(int j=0; j<g->n_edges; j++)
        {
            int link;
            fscanf(file, "%d", &link);
            g->nodes[currentNumber].edges[j] = &g->nodes[link];
        }
    }
    return g;
}

void printGraphAlt(GRAPH* graph)
{
    for(int i=0; i<graph->n_nodes; i++)
    {
        printf("%d ", i);
        for(int j=0; j<graph->n_edges; j++)
        {
            printf("%d ", graph->nodes[i].edges[j]->index);
        }
        printf("spin %d\n", graph->nodes[i].spin);
    }
}

GRAPH* getGraphFromPython(int nodes, int edges)
{
    char command[50];
    sprintf(command, "python graf_console.py %d %d", nodes, edges);
    FILE* pythonPipe = popen(command, "r");

    if(!pythonPipe)
    {
        printf("Error opening pipe to python");
        return 0;
    }

    int n_edges = edges;
    int n_nodes = nodes;
    GRAPH* g = allocateGraph(n_nodes,n_edges);

    for(int i=0; i<g->n_nodes; i++)
    {
        for(int j=0; j<g->n_edges; j++)
        {
            int link;
            fscanf(pythonPipe, "%d", &link);
            g->nodes[i].edges[j] = &g->nodes[link];
        }
    }
    pclose(pythonPipe);
    return g;

}

