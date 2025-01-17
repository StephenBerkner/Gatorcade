/*
 * Pong.h
 *
 * Created: 9/23/2019 10:06:56 PM
 *  Author: sberk
 */ 


#ifndef PONG_H_
#define PONG_H_
#include <stdbool.h>

#include "USART.h"

//#include "LEDMatrix.h"

#define BOARD_WIDTH			32
#define BOARD_HEIGHT		32

#define PADDLE_WIDTH		6
#define PADDLE_HEIGHT		2

#define PLAYER_ONE_PADDLE_ROW 25 
#define PLAYER_TWO_PADDLE_ROW 4

#define BALL_SIDE_LENGTH	2


//board constants 0->constant
#define NUM_BALL_COLS 28
#define NUM_BALL_ROWS 20

//paddle constants 0-> constant
#define NUM_PADDLE_COLS 22


//ball and paddle coordinates
//uint8_t PlayerOnePaddleRow;
uint8_t PlayerOnePaddleCol;
uint8_t PlayerOnePaddleSpeed;
bool PlayerOneGoingRight;
uint8_t PlayerOneScore;


//ball and paddle coordinates
//uint8_t PlayerTwoPaddleRow;
uint8_t PlayerTwoPaddleCol;
uint8_t PlayerTwoPaddleSpeed;
bool PlayerTwoGoingRight;
uint8_t PlayerTwoScore;

//if the score is 2-2 sudden death mode will be enabled
bool suddenDeath;
//bounding box defined by upper left corner
uint8_t BallRow;
uint8_t BallCol;

uint8_t BallXSpeed;
uint8_t BallYSpeed;

bool BallGoingDown;
bool BallGoingRight;

bool GameResuming = false;


void PongInit(){
	
	//PlayerOnePaddleRow =  //(HEIGHT + PADDLE_HEIGHT) / 2;
	PlayerOnePaddleCol = 0x0F;//PADDLE_BORDER;
	//PlayerOnePaddleSpeed = 0;
	
	//PlayerTwoPaddleRow = (HEIGHT + PADDLE_HEIGHT) / 2;
	PlayerTwoPaddleCol = 0x0F;// (WIDTH/2) - PADDLE_BORDER;
	//PlayerTwoPaddleSpeed = 0;
	
	//set scores to 0
	PlayerOneScore = 0x00;
	PlayerTwoScore = 0x00;
	
	suddenDeath = false;
	
	//place ball in player one's area
	//change this to random or something more complex later
	BallRow = 0x0A;// (HEIGHT + BALL_SIDE_LENGTH) / 2;
	BallCol = 0x0A;//WIDTH / 4 + BALL_SIDE_LENGTH / 2;
	
	BallXSpeed = 0x01;
	BallYSpeed = 0x01;
	
	//Ball is going down and to the right
	//can change this to be more complex later
	BallGoingDown = true;
	BallGoingRight = true;
	
	//port inits
	//set first 5 pins as output pins
	
	//paddle 1 0-4,
	DDRA |= 0x1F;
	//PORTA = 0x00;
	
	//paddle 2 0-3,6
	DDRB |= 0x4F;
	//PORTB = 0x00;
	
	//Ball Col PORTC 0-1, 6-7, PORTD 7
	DDRC |= 0xC3;
	DDRD |= 0x80;
	//PORTC = 0x00;
	
	//Ball Row PORTD 1, 3-6
	DDRD |= 0x7A;
	//PORTD = 0x00;
	
	//Initialize USART
	USARTInit();
	
}


//set Player 1 paddle column
void SetPlayerOnePaddleCol(uint8_t col){
	switch (col){
		case 0:
			PORTA &= ~0x1F;
			
			break;
		case 1:
			PORTA &= ~0x1F;
			
			PORTA|= 0x01;
			break;
		case 2:
			PORTA &= ~0x1F;
			
			PORTA |= 0x02;
			break;
		case 3:
			PORTA &= ~0x1F;
			
			PORTA |= 0x03;
			break;
		case 4:
			PORTA &= ~0x1F;
			
			PORTA |= 0x04;
			break;
		case 5:
			PORTA &= ~0x1F;
			
			PORTA |= 0x05;
			break;
		case 6:
			PORTA &= ~0x1F;
			
			PORTA |= 0x06;
			break;
		case 7:
			PORTA &= ~0x1F;
			
			PORTA |= 0x07;
			break;
		case 8:
			PORTA &= ~0x1F;
			
			PORTA |= 0x08;
			break;
		case 9:
			PORTA &= ~0x1F;
			
			PORTA |= 0x09;
			break;
		case 10:
			PORTA &= ~0x1F;
			
			PORTA |= 0x0A;
			break;
		case 11:
			PORTA &= ~0x1F;
			
			PORTA |= 0x0B;
			break;
		case 12:
			PORTA &= ~0x1F;
			
			PORTA |= 0x0C;
			break;
		case 13:
			PORTA &= ~0x1F;
			
			PORTA |= 0x0D;
			break;
		case 14:
			PORTA &= ~0x1F;
			
			PORTA |= 0x0E;
			break;
		case 15:
			PORTA &= ~0x1F;
			
			PORTA |= 0x0F;
			break;
		case 16:
			PORTA &= ~0x1F;
			
			PORTA |= 0x10;
			break;
		case 17:
			PORTA &= ~0x1F;
			
			PORTA |= 0x11;
			break;
		case 18:
			PORTA &= ~0x1F;
			
			PORTA |= 0x12;
			break;
		case 19:
			PORTA &= ~0x1F;
			
			PORTA |= 0x13;
			break;
		case 20:
			PORTA &= ~0x1F;
			
			PORTA |= 0x14;
			break;
		case 21:
			PORTA &= ~0x1F;
			
			PORTA |= 0x15;
			break;
		case 22:
			PORTA &= ~0x1F;
			
			PORTA |= 0x16;
			break;
		case 23:
			PORTA &= ~0x1F;
				
			PORTA |= 0x17;
			break;
		case 24:
			PORTA &= ~0x1F;
				
			PORTA |= 0x18;
			break;
		case 25:
			PORTA &= ~0x1F;
				
			PORTA |= 0x19;
			break;
		case 26:
			PORTA &= ~0x1F;
				
			PORTA |= 0x1A;
			break;
		//case 27:
			//PORTA &= ~0x1F;
				//
			//PORTA |= 0x1B;
			//break;	
		default:
			break;
		
	}
}

void DisablePlayerOnePaddle(){
	//set select to undefined value (0x1E)
	//clear port
	PORTA &= ~0x1F;
	
	//PORTA |= 0x;
	
}


//set Player 2 paddle column
void SetPlayerTwoPaddleCol(uint8_t col){
	switch (col){
		case 0:
			PORTB &= ~0x4F;

			break;
		case 1:
			PORTB &= ~0x4F;
			
			PORTB |= 0x01;
			break;
		case 2:
			PORTB &= ~0x4F;
			
			PORTB |= 0x02;
			break;
		case 3:
			PORTB &= ~0x4F;
			
			PORTB |= 0x03;
			break;
		case 4:
			PORTB &= ~0x4F;
			
			PORTB |= 0x04;
			break;
		case 5:
			PORTB &= ~0x4F;
			
			PORTB |= 0x05;
			break;
		case 6:
			PORTB &= ~0x4F;
			
			PORTB |= 0x06;
			break;
		case 7:
			PORTB &= ~0x4F;
			
			PORTB |= 0x07;
			break;
		case 8:
			PORTB &= ~0x4F;
			
			PORTB |= 0x08;
			break;
		case 9:
			PORTB &= ~0x4F;
			
			PORTB |= 0x09;
			break;
		case 10:
			PORTB &= ~0x4F;
			
			PORTB |= 0x0A;
			break;
		case 11:
			PORTB &= ~0x4F;
			
			PORTB |= 0x0B;
			break;
		case 12:
			PORTB &= ~0x4F;
			
			PORTB |= 0x0C;
			break;
		case 13:
			PORTB &= ~0x4F;
			
			PORTB |= 0x0D;
			break;
		case 14:
			PORTB &= ~0x4F;
			
			PORTB |= 0x0E;
			break;
		case 15:
			PORTB &= ~0x4F;
			
			PORTB |= 0x0F;
			break;
		case 16:
			PORTB &= ~0x4F;
			
			PORTB |= 0x40;
			break;
		case 17:
			PORTB &= ~0x4F;
			
			PORTB |= 0x41;
			break;
		case 18:
			PORTB &= ~0x4F;
			
			PORTB |= 0x42;
			break;
		case 19:
			PORTB &= ~0x4F;
			
			PORTB |= 0x43;
			break;
		case 20:
			PORTB &= ~0x4F;
			
			PORTB |= 0x44;
			break;
		case 21:
			PORTB &= ~0x4F;
			
			PORTB |= 0x45;
			break;
		case 22:
			PORTB &= ~0x4F;
		
			PORTB |= 0x46;
			break;
		case 23:
			PORTB &= ~0x4F;
			
			PORTB |= 0x47;
			break;
		case 24:
			PORTB &= ~0x4F;
				
			PORTB |= 0x48;
			break;
		case 25:
			PORTB &= ~0x4F;
				
			PORTB |= 0x49;
			break;
		case 26:
			PORTB &= ~0x4F;
		
			PORTB |= 0x4A;
			break;
		//case 27:
			//PORTB &= ~0x4F;
		//
			//PORTB |= 0x15;
			//break;

		default:
			break;
		
	}
}

void DisablePlayerTwoPaddle(){
	
	//set to undefined value (0x1E) 
	//clear port
	PORTB &= ~0x4F;
	//PORTB |= 0x4C;
}


//NEEDS TO BE EDITED
//set Ball column
void SetBallCol(uint8_t col){
	switch (col){
		case 0:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			break;
		case 1:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x01;
			break;
		case 2:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x02;
			break;
		case 3:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x03;
			break;
		case 4:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x40;
			break;
		case 5:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x41;
			break;
		case 6:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
				
			PORTC |= 0x42;
			break;
		case 7:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x43;
			break;
		case 8:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x80;
			break;
		case 9:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x81;
			break;
		case 10:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x82;
			break;
		case 11:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x83;
			break;
		case 12:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0xC0;
			break;
		case 13:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0xC1;
			break;
		case 14:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0xC2;
			break;
		case 15:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0xC3;
			break;
		case 16:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTD |= 0x80;
			break;
		case 17:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x01;
			PORTD |= 0x80;
			break;
		case 18:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x02;
			PORTD |= 0x80;
			break;
		case 19:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x03;
			PORTD |= 0x80;
			break;
		case 20:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x40;
			PORTD |= 0x80;
			break;
		case 21:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x41;
			PORTD |= 0x80;
			break;
		case 22:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x42;
			PORTD |= 0x80;
			break;
		case 23:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x43;
			PORTD |= 0x80;
			break;
		case 24:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x80;
			PORTD |= 0x80;
			break;
		case 25:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x81;
			PORTD |= 0x80;
			break;
		case 26:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x82;
			PORTD |= 0x80;
			break;
		case 27:
			PORTC &= ~0xC3;
			PORTD &= ~0x80;
			
			PORTC |= 0x83;
			PORTD |= 0x80;
			break;
		default:
			break;
		
	}
}

//NEEDS TO BE EDITED
//set Ball row
void SetBallRow(uint8_t row){
	switch (row){
		case 0:
			PORTD &= ~0x7A;
			PORTD |= 0b00000000;
			break;
		case 1:
			PORTD &= ~0x7A;
			PORTD |= 0b00000010;
			break;
		case 2:
			PORTD &= ~0x7A;
			PORTD |= 0b00001000;
			break;
		case 3:
			PORTD &= ~0x7A;
			PORTD |= 0b00001010;
			break;
		case 4:
			PORTD &= ~0x7A;
			PORTD |= 0b00010000;
			break;
		case 5:
			PORTD &= ~0x7A;
			PORTD |= 0b00010010;
			break;
		case 6:
			PORTD &= ~0x7A;
			PORTD |= 0b00011000;
			break;
		case 7:
			PORTD &= ~0x7A;
			PORTD |= 0b00011010;
			break;
		case 8:
			PORTD &= ~0x7A;
			PORTD |= 0b00100000;
			break;
		case 9:
			PORTD &= ~0x7A;
			PORTD |= 0b00100010;
			break;
		case 10:
			PORTD &= ~0x7A;
			PORTD |= 0b00101000;
			break;
		case 11:
			PORTD &= ~0x7A;
			PORTD |= 0b00101010;
			break;
		case 12:
			PORTD &= ~0x7A;
			PORTD |= 0b00110000;
			break;
		case 13:
			PORTD &= ~0x7A;
			PORTD |= 0b00110010;
			break;
		case 14:
			PORTD &= ~0x7A;
			PORTD |= 0b00111000;
			break;
		case 15:
			PORTD &= ~0x7A;
			PORTD |= 0b00111010;
			break;
		case 16:
			PORTD &= ~0x7A;
			PORTD |= 0b01000000;
			break;
		case 17:
			PORTD &= ~0x7A;
			PORTD |= 0b01000010;
			break;
		case 18:
			PORTD &= ~0x7A;
			PORTD |= 0b01001000;
			break;
		case 19:
			PORTD &= ~0x7A;
			PORTD |= 0b01001010;
			break;
		case 20:
			PORTD &= ~0x7A;
			PORTD |= 0b01010000;
			break;
		case 21:
			PORTD &= ~0x7A;
			PORTD |= 0b01010010;
			break;
		case 22:
			PORTD &= ~0x7A;
			PORTD |= 0b01011000; 
			break;
		case 23:
			PORTD &= ~0x7A;
			PORTD |= 0b01011010;
			break;
		case 24:
			PORTD &= ~0x7A;
			PORTD |= 0b01100000;
			break;
		case 25:
			PORTD &= ~0x7A;
			PORTD |= 0b01100010;
			break;
		case 26:
			PORTD &= ~0x7A;
			PORTD |= 0b01101000;
			break;
		case 27:
			PORTD &= ~0x7A;
			PORTD |= 0b01101010;
			break;
		default:
			break;
		
			}
}

void DisableBall(){
	
	PORTC &= ~0xC3;
	PORTD &= ~0xFA;
	
	//set col to undefined value (0x1F)
	PORTC |= 0x03;
	PORTD |= 0x80;
	
	//set row to undefined value (0x1F)
	PORTD |= 0x7A;
				
}


bool Collision(uint8_t paddleCol, uint8_t paddleRow, uint8_t ballRow, uint8_t ballCol){
	//check columns
	//if ball is inside of paddle
	if ((ballCol <= (paddleCol + PADDLE_WIDTH) && ((ballCol + BALL_SIDE_LENGTH) >= paddleCol))){
		if (paddleRow == 0){
			
			if (ballRow == 0x10 || ballRow == 0x11){
				return true;
			}
		} else {
			if (ballRow = 0x00 || ballRow ==  0x01){
				return true;
			}
		}
	}
		return false;
	
}

bool PointScored(uint8_t paddleCol, uint8_t paddleRow, uint8_t ballRow, uint8_t ballCol){
	//check paddle row and ball row to see if ball has advanced past paddle
	//if the ball is past the paddle a point has been scored
	if (paddleRow != 0){
		if (ballRow <= 0x00)
			return true;
			
	} else{
		
		 if (ballRow >= 0x11)
			return true;
	}
	
	return false;

}

void DisplayScores(){
	
	//disable pong components
	DisableBall();
	DisablePlayerOnePaddle();
	DisablePlayerTwoPaddle();
	
	//turn on score board frame
	PORTC |= 0xC3;
	PORTD |= 0xFA;
	
	
	
	//set player one score display
	
	switch (PlayerOneScore){
		case 0x00:
			PORTA &= ~0x1F;
			PORTA |= 0x1B;
			break;
		case 0x01:
			PORTA &= ~0x1F;
			PORTA |= 0x1C;
			break;
		case 0x02:
			PORTA &= ~0x1F;
			PORTA |= 0x1D;
			break;
		case 0x03:
			PORTA &= ~0x1F;
			PORTA |= 0x1E;
			break;
	}
	
	
	//set player two score display
	
	switch(PlayerTwoScore){
		case 0x00:
			PORTB &= ~0x4F;
			PORTB |= 0x4B;
			break;
		case 0x01:
			PORTB &= ~0x4F;
			PORTB |= 0x4C;
			break;
		case 0x02:
			PORTB &= ~0x4F;
			PORTB |= 0x4D;
			break;
		case 0x03:
			PORTB &= ~0x4F;
			PORTB |= 0x4E;
			break;
	}
	
	
	_delay_ms(2500);
			
	
}

void PlayerOneScored(){
		
	//disable pong components
	DisableBall();
	DisablePlayerOnePaddle();
	DisablePlayerTwoPaddle();
	
	//increment player one score
	PlayerOneScore += 1;
	
	//turn on P1 Point Screen
	PORTA |= 0x1F;
	
	
	BallCol = 0x0A;
	BallRow = 0x0A;
	
	//if sudden death display sudden death screen
	if (PlayerOneScore == 2 && PlayerTwoScore == 2){
		suddenDeath = true;
		DisplaySuddenDeathScreen();
		
		for (int i = 0; i < 9; i++){
			PlaySuddenDeathAudio();
			_delay_ms(70);
		}	
	} else {

		_delay_ms(3000);
	
	}
		
	//game will be resuming after point is scored
	//add a delay so players know where the ball
	//is before resuming play
	GameResuming = true;
	
	
}


void PlayerTwoScored(){


	//disable pong components
	DisableBall();
	DisablePlayerOnePaddle();
	DisablePlayerTwoPaddle();
	
	//increment player two score
	PlayerTwoScore += 1;
	
	//turn on P2 Point Screen
	PORTB |= 0x4F;
	
	
	BallCol = 0x0A;
	BallRow = 0x0A;
	
	//if sudden death display sudden death screen
	if (PlayerOneScore == 2 && PlayerTwoScore == 2){
		suddenDeath = true;
		DisplaySuddenDeathScreen();
		
		for (int i = 0; i < 9; i++){
			PlaySuddenDeathAudio();
			_delay_ms(70);
		}	
		
	} else {
		_delay_ms(3000);
	}
	
	//game will be resuming after point is scored
	//add a delay so players know where the ball
	//is before resuming play
	GameResuming = true;

}

//add logic here
void DisplaySuddenDeathScreen(){
	
	
}

void RedrawScreen(){
	
	//set paddle location appropriately	
	SetPlayerOnePaddleCol(PlayerOnePaddleCol);
	SetPlayerTwoPaddleCol(PlayerTwoPaddleCol);
	
	//set ball location appropriately
	SetBallCol(BallCol);
	SetBallRow(BallRow);
	
}

void UpdateFrame(){
	
	
	//determine if ball is colliding
	
	//check left wall collision
	if (BallCol == 0x00){
		//play wall bounce audio
		PlayWallBounceAudio();
		
		BallGoingRight = !BallGoingRight;
	}
	
	//check right wall collision
	if (BallCol >= 0x1B){
		//play wall bounce audio
		PlayWallBounceAudio();
		
		BallGoingRight = !BallGoingRight;
	}
	
	
	
	//check player 1 paddle collision
	if (Collision(PlayerOnePaddleCol, 0, BallRow, BallCol)){
		//collision has occurred
		
		//play paddle bounce audio
		PlayPaddleBounceAudio();
		
		//reverse ball direction
		BallGoingDown = !BallGoingDown;
		
	}
	
	
	//check player 2 paddle collision
	if (Collision(PlayerTwoPaddleCol, 20, BallRow, BallCol)){
		//collision has occurred
		
		//play paddle bounce audio
		PlayPaddleBounceAudio();
		
		//reverse ball direction
		BallGoingDown = !BallGoingDown;
	}
	
	//collision has not occurred, it is possible that a point has been scored
	
	//point scored on player one
	if (PointScored(PlayerOnePaddleCol, 0, BallRow, BallCol)){
		//Therefore PlayerTwo has Scored
		
		PlayGamePointAudio();
		//BallGoingDown = !BallGoingDown;
		PlayerTwoScored();
		
		DisplayScores();
		
	}
	
	//point scored on player two
	if (PointScored(PlayerTwoPaddleCol, 20, BallRow, BallCol)){
		//therefore Player One has scored
		//BallGoingDown = !BallGoingDown;
		PlayGamePointAudio();
		PlayerOneScored();
		
		DisplayScores();
	}
	
	//no collisions have been detected and no points have been scored 
	//move paddles accordingly
	
	//set player one paddle position
	//use bitmask
	switch (PlayerOneUSARTData & 0x0F) {
		case 0x00:
			PlayerOnePaddleCol = 0x01;
			break;
		case 0x01:
			PlayerOnePaddleCol = 0x02;
			break;
		case 0x02:
			PlayerOnePaddleCol = 0x03;
			break;
		case 0x03:
			PlayerOnePaddleCol = 0x05;
			break;
		case 0x04:
			PlayerOnePaddleCol = 0x07;
			break;
		case 0x05:
			PlayerOnePaddleCol = 0x09;
			break;
		case 0x06:
			PlayerOnePaddleCol = 0x0B;
			break;
		case 0x07:
			PlayerOnePaddleCol = 0x0D;
			break;
		case 0x08:
			PlayerOnePaddleCol = 0x0F;
			break;
		case 0x09:
			PlayerOnePaddleCol = 0x11;
			break;
		case 0x0A:
			PlayerOnePaddleCol = 0x14;
			break;
		case 0x0B:
			PlayerOnePaddleCol = 0x16;
			break;
		case 0x0C:
			PlayerOnePaddleCol = 0x17;  
			break;
		case 0x0D:
			PlayerOnePaddleCol = 0x18;
			break;
		default:
			break;
		
	}

	//set player two paddle position
	
	switch (PlayerTwoUSARTData & 0x0F)
	{
		case 0x00:
			PlayerTwoPaddleCol = 0x01;
			break;
		case 0x01:
			PlayerTwoPaddleCol = 0x02;
			break;
		case 0x02:
			PlayerTwoPaddleCol = 0x03;
			break;
		case 0x03:
			PlayerTwoPaddleCol = 0x05;
			break;
		case 0x04:
			PlayerTwoPaddleCol = 0x07;
			break;
		case 0x05:
			PlayerTwoPaddleCol = 0x09;
			break;
		case 0x06:
			PlayerTwoPaddleCol = 0x0B;
			break;
		case 0x07:
			PlayerTwoPaddleCol = 0x0D;
			break;
		case 0x08:
			PlayerTwoPaddleCol = 0x0F;
			break;
		case 0x09:
			PlayerTwoPaddleCol = 0x11;
			break;
		case 0x0A:
			PlayerTwoPaddleCol = 0x14;
			break;
		case 0x0B:
			PlayerTwoPaddleCol = 0x16;
			break;
		case 0x0C:
			PlayerTwoPaddleCol = 0x17;
			break;
		case 0x0D:
			PlayerTwoPaddleCol = 0x18;
			break;
		default:
			break;
		
	}
	if (BallGoingDown){
		BallRow += BallYSpeed;	
	} else {
		BallRow -= BallYSpeed;
	}		
	
	//move balls accordingly

	
	if (BallGoingRight){
		BallCol += BallXSpeed;
			
	} else {
		BallCol -= BallXSpeed;
	}
	
	RedrawScreen();
	
}



void PlayPong(void){
	
	_delay_ms(300);
	
	while (1){
		if (GameResuming){
			_delay_ms(1000);
			GameResuming = false;
		}
		UpdateFrame();
		
		//go back to main menu
		if ( (((PlayerOneUSARTData & 0x80) == 0x80) || ((PlayerTwoUSARTData & 0x80) == 0x80) ) != 0x00){
			break;
		}
		
		//speed up the game if in sudden death mode
		if (suddenDeath){
			
			_delay_ms(55);
		
		} else {
		
			_delay_ms(80);
				
		}		
		
		if (PlayerOneScore == 3 || PlayerTwoScore == 3){
			//put victory screen function call here
			
			//game is over
			break;
		}
	}
	
	//_delay_ms(17);
	
	//play game over audio
	PlayGameOverAudio();
	
	//need to insert delay for length of audio
	
	//go back to menu
	MenuInit();
	MenuSelect();
}

//startup test to make sure ball is playable
void StartupTest(){
	
	
	for (uint8_t row = 0; row < NUM_BALL_ROWS; row++){
		for (uint8_t col = 0; col < NUM_BALL_COLS; col++){
			BallRow = row;
			BallCol = col;
			//configure ball
			SetBallCol(col);
			SetBallRow(row);
			
			SetPlayerOnePaddleCol(col);
			SetPlayerTwoPaddleCol(col);
			_delay_ms(60);
		
		}
	}
	
	
}



#endif /* PONG_H_ */