/*
 * Menu.h
 *
 * Created: 11/16/2019 5:06:43 PM
 *  Author: sberk
 */ 


#ifndef MENU_H_
#define MENU_H_

#include <stdbool.h>
#include "Audio.h"

bool GameSel = true;

bool neutralAcheived = false;

void MenuInit(){
	
	//using PORTA 5 and 6
	
	DDRA |= 0x60;
	
	//Bit 5 used to determine if in menu mode
	//stay in menu mode until game selected
	PORTA |= 0x20;
	
	//initialize audio
	AudioInit();
	
	
}

//used to determine which game is 
void MenuSelect(){
	
	_delay_ms(2000);
	
	while (1){
		
		//make sure joystick is neutral to ensure one switch per joystick movement
		if (((PlayerOneUSARTData) & 0x70 == 0x00) || ((PlayerTwoUSARTData & 0x70) == 0x00) ){
			neutralAcheived = true;
		}


		//move select up and down to determine game

		if ( ((((PlayerOneUSARTData & 0x70) == 0x30) || ((PlayerOneUSARTData & 0x70) == 0x70) || ((PlayerTwoUSARTData & 0x70) == 0x30) || ((PlayerTwoUSARTData & 0x70) == 0x70)) != 0x00) && neutralAcheived){
			//PORTA ^= 0x40;
			//GameSel ^= GameSel;
			if (GameSel){
				GameSel = false;
				PORTA |= 0x40;
				
			} else{
				GameSel = true;
				PORTA &= ~0x40;
			}
			
			neutralAcheived = false;
			//_delay_ms(30);
		}
	
		//select game mode
		if ( (((PlayerOneUSARTData & 0x80) == 0x80) || ((PlayerTwoUSARTData & 0x80) == 0x80) ) != 0x00){
			PORTA &= ~0x20;
			
			//_delay_ms(600);		
			break;
		}	
		
		_delay_ms(400);
	}
	
	//play menu select audio
	PlayMenuSelectAudio();
	
	//game sel true for first game (pong)
	if (GameSel){
		//initialize ports and pong variables appropriately
		PongInit();
	
		//play pong game
		PlayPong();
	} else {
		
		//initialize ports and maze runner variables appropriately
		MazeRunnerInit();
		
		//play Maze Runner game
		PlayMazeRunner();
	}
	
}



#endif /* MENU_H_ */