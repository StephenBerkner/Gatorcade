/*
 * Master.c
 *
 * Created: 8/25/2019 11:52:37 PM
 * Author : sberk
 */ 

//includes
#include <avr/io.h>
#include <util/delay.h>

#include "Pong.h"
#include "Menu.h"
#include "USART.h"

int main(void)
{
	

	//initialize USART ports and variables appropriately
	USARTInit();
	
	//Startup test if desired
	//StartupTest();
	
	//intialize menu
	MenuInit();
	//run Menu
	MenuSelect();
	//run pong game
	//PlayPong();

}

