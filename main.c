#include "Ising.h"
#include "parseGraph.h"
#include "Graphs.h"
#include "Utils.h"
#include "Interface.h"
#define N_EDGES 3
#define N_NODES 10000

int main(void)
{

	printf("Witam\n");
	int n_edges = N_EDGES;
	int n_nodes =N_NODES;
    GRAPH* g = getGraphFromPython(n_nodes, n_edges);
    SPIN s = SPIN_RANDOM;
    fillSpins(g, s);


    float T = 0.0f;
    int choice = SMALLSTEP;
    printMenu();
    while(scanf("%d",&choice) && choice!=EXIT){

    	switch(choice){
    	case SMALLSTEP :
    		printf("small step jest bezuzyteczy\n");
    		break;
    	case BIGSTEP :
    		applyBigMCStep(g);
    		printf("Applied big step\nPS big step tez jest bezuzyteczny\n");
    		break;
    	case TIME_SPECTRUM :
    		saveTimeSpectrum(g);
    		break;
    	case TEMP_SPECTRUM :
    		saveTempSpectrum(g);
    		break;
    	case SET_TEMP :
    		T=getTempSelect();
    		setTemp(T,g);
    		break;
    	case SET_SPINS :
    		s=getNSelect(choice);
    		fillSpins(g,s);
    		break;
    	case SET_N_EDGES :
    		n_edges=getNSelect(choice);
    		break;
    	case SET_N_NODES :
    		n_nodes = getNSelect(choice);
    		break;
    	case CREATE_GRAPH :
    		g = getGraphFromPython(n_nodes,n_edges);
    		fillSpins(g,s);
    		break;
    	case EXIT :
    		break;
    	default : return 0;
    	}
    	printMenu();
    }




    return 0;
}
