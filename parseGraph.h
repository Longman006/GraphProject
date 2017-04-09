#ifndef PARSE_GRAPH_
#define PARSE_GRAPH_

#include "Graphs.h"
#include <stdio.h>
GRAPH* getGraph(FILE* file);
GRAPH* getGraphFromPython(int, int);
void printGraphAlt(GRAPH* graph);
GRAPH* allocateGraph(int ,int);
#endif // PARSE_GRAPH_

