/*
 * Interface.c
 *
 *  Created on: 30.03.2017
 *      Author: longman
 */

#include "Interface.h"
void printMenu(void){
	for(int i = SMALLSTEP ; i<=EXIT ; i++){
		printf("%d : %s\n",i,getOptionName(i));
	}
}
const char* getOptionName(enum Options o){
	switch(o){
	case SMALLSTEP : return "Small step";
	case BIGSTEP : return "Big step";
	case TIME_SPECTRUM : return "Time spectrum";
	case TEMP_SPECTRUM : return "Temperature spectrum";
	case SET_TEMP : return "Set temperature";
	case SET_SPINS : return "Set spins (-1,0,+1) ";
	case SET_N_EDGES : return "Set number of edges";
	case SET_N_NODES : return "Set number of nodes";
	case CREATE_GRAPH : return "Create new Graph";
	case EXIT : return "Exit";
	default : return "No such option";
	}
}


void testOptions(void){

	printf("getOptionName(SMALLSTEP) : %s ",
			getOptionName(SMALLSTEP));
	printMenu();

}

SPIN getSpinSelect(void){
	fprintf(stdout," %d: Spins Up\n %d: Spins down \n %d: Spins random\n",SPIN_UP,SPIN_DOWN,SPIN_RANDOM);
	SPIN choice=0;
	if(scanf("%d",&choice)){
		fprintf(stdout,"Selected : %d \n",choice);
	}
	else
		fprintf(stdout,"ERROR returning %d",choice);
	return choice;
}
float getTempSelect(void){
	float T=0.0f;
	puts(getOptionName(SET_TEMP));
	if(scanf("%f",&T)){
		fprintf(stdout,"Selected : %f \n",T);
	}
		else
			fprintf(stdout,"ERROR returning %f",T);
	return T;
}
int getNSelect(enum Options o){
	puts(getOptionName(o));
	int choice=0;
	if(scanf("%d",&choice)){
		fprintf(stdout,"Selected : %d \n",choice);
	}
	else
		fprintf(stdout,"ERROR returning %d",choice);
	return choice;
}

