#include "Ising.h"
#include "parseGraph.h"
#include "Graphs.h"

#define N_EDGES 10000
#define N_NODES 5

int main(void)
{
    float T = 0.05f;
    float kb = 1.0f;

    FILE* f = fopen("wynik10000.txt", "r");
    //FILE* wynik = fopen("symulacja10000.txt", "w");
    GRAPH* g = getGraph(f);
    //connectGraph(g);
    fillRandomSpins(g);
    //printGraphAlt(g);

    printf("\n");
    char choice = 'a';
    for(int i=0;;i++)
    {

        choice = getch();
        switch(choice)
        {
            case 's':                           //small step
                applySmallMCStep(g, T, kb);
                break;
            case 'b':                           //big step
                applyBigMCStep(g, T, kb);
                break;
            case 'v':
                for(int i=0; i<200; i++)        //very big step
                    applyBigMCStep(g, T, kb);
                break;
            case 'e':                           //exit
                //fclose(f);
                return 0;
        }
        printGraphStats(g);

        //Writing to file
        /*
        applySmallMCStep(g, 0.22f, 1.0f);
        int spinUp = getSpinUpNum(g);
        fprintf(wynik, "%d %d\n", i, spinUp);
        if(spinUp == 0 || spinUp ==10000)
            break;
            */



    }
    //fclose(wynik);
    //fclose(f);


    return 0;
}
