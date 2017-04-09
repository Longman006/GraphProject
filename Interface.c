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
	case SET_SPINS : return "Set spins ";
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

