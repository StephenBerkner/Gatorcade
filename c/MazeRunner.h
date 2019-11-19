/*
 * MazeRunner.h
 *
 * Created: 11/17/2019 10:55:09 PM
 *  Author: sberk
 */ 


#ifndef MAZERUNNER_H_
#define MAZERUNNER_H_

#include <stdbool.h>

#include "USART.h"

void MazeRunnerInit(){
	
}

void PlayMazeRunner(){
	
	_delay_ms(300);
	
	while (1){
		FrameUpdate();
		
		//go back to main menu
		if ( (((PlayerOneUSARTData & 0x80) == 0x80) || ((PlayerTwoUSARTData & 0x80) == 0x80) ) != 0x00){
			break;
		}
			
		_delay_ms(150);
	}
	
	//go back to menu
	MenuInit();
	MenuSelect();

	
}

void FrameUpdate(){
	
}


#endif /* MAZERUNNER_H_ */