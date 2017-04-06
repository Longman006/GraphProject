#include "Ising.h"
#include "parseGraph.h"
#include "Graphs.h"
#include "Utils.h"
#include "Statistics.h"
#include "Interface.h"
#define N_EDGES 10000
#define N_NODES 3

int main(void)
{
    //FILE* f = fopen("wynik10000.txt", "r");
    GRAPH* g = getGraphFromPython(N_EDGES, N_NODES);
    fillSameSpins(g, SPIN_UP);
    //printGraphAlt(g);

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
    		puts(getOptionName(choice));
    		if(scanf("%f",&T)){
    			setTemp(T,g);
    		}
    		break;
    	case EXIT :
    		break;
    	default : return 0;
    	}
    	printMenu();
    }




    return 0;
}
