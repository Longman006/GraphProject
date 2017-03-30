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
	case EXIT : return "Exit";
	default : return "No such option";
	}
}


void testOptions(void){

	printf("getOptionName(SMALLSTEP) : %s ",
			getOptionName(SMALLSTEP));
	printMenu();

}

