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
    float TMin = 0.0f;
    float TMax = 0.0f;
    float TDelta = 1.0f;
    int choice = EXIT;
    printMenu();
    while(scanf("%d",&choice) && choice!=EXIT){
    	switch(choice){
    	case TIME_SPECTRUM :
    		saveTimeSpectrum(g);
    		break;
    	case TEMP_SPECTRUM :
    		saveTempSpectrum(g,TMin,TMax,TDelta,true);
    		break;
    	case SET_TMIN :
    		TMin = getXSelect(choice);
    		break;
    	case SET_TMAX :
    		TMax = getXSelect(choice);
    		break;
    	case SET_DELTAT :
    		TDelta = getXSelect(choice);
    		break;
    	case SET_TEMP :
    		T=getXSelect(choice);
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
    	case TC_N_NODES :
    		fclose(saveTcSpectrum(n_edges,true));
    		break;
    	case CRITICAL_TEMP_PLOT :
    		plotCriticalTemp();
    		break;
    	case EXIT :
    		return 1;
    	default : return 0;
    	}
    	printMenu();
    }

    return 0;
}
