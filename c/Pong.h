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

//ball and paddle coordinates
//uint8_t PlayerTwoPaddleRow;
uint8_t PlayerTwoPaddleCol;
uint8_t PlayerTwoPaddleSpeed;
bool PlayerTwoGoingRight;

//bounding box defined by upper left corner
uint8_t BallRow;
uint8_t BallCol;

uint8_t BallXSpeed;
uint8_t BallYSpeed;

bool BallGoingDown;
bool BallGoingRight;


//debugging
bool p1CollisionOccuring = false;
bool p2CollisionOccuring = true;

void PongInit(){
	
	//PlayerOnePaddleRow =  //(HEIGHT + PADDLE_HEIGHT) / 2;
	PlayerOnePaddleCol = 0x0F;//PADDLE_BORDER;
	//PlayerOnePaddleSpeed = 0;
	
	//PlayerTwoPaddleRow = (HEIGHT + PADDLE_HEIGHT) / 2;
	PlayerTwoPaddleCol = 0x0F;// (WIDTH/2) - PADDLE_BORDER;
	//PlayerTwoPaddleSpeed = 0;
	
	//place ball in player one's area
	//change this to random or something more complex later
	BallRow = 0x0F;// (HEIGHT + BALL_SIDE_LENGTH) / 2;
	BallCol = 0x0F;//WIDTH / 4 + BALL_SIDE_LENGTH / 2;
	
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
		default:
			break;
		
	}
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
			
			PORTB |= 0x15;
			break;
		default:
			break;
		
	}
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

bool Collision(uint8_t paddleCol, uint8_t paddleRow, uint8_t ballRow, uint8_t ballCol){
	//ball is in the middle of the board
	//if (ballRow > 0 || ballRow < 25) //  (PLAYER_ONE_PADDLE_ROW + PADDLE_HEIGHT) || ballRow < PLAYER_TWO_PADDLE_ROW)
		//return false;
	//
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
	
	//check rows
	//if ball is outside of paddle row
	//if ((ballRow > (paddleRow + PADDLE_HEIGHT)) || ((ballRow + BALL_SIDE_LENGTH) < paddleRow))
		//return false;
	
	//ball must be colliding 
	//return true;
	
	
	
	
	
}

bool PointScored(uint8_t paddleCol, uint8_t paddleRow, uint8_t ballRow, uint8_t ballCol){
	
	////check if ball is in valid area for potential score
	//if (ballRow == 0x00 || ballRow == 0x14){//if (ballRow <= (PLAYER_ONE_PADDLE_ROW + PADDLE_HEIGHT) || ballRow >= PLAYER_TWO_PADDLE_ROW){
		////ball is in valid row
		//
		//if ((ballCol >= (paddleCol + PADDLE_WIDTH)) || ((ballCol + BALL_SIDE_LENGTH) >= paddleCol)){
			////ball is in valid column
			//
			////if ((ballRow <= (paddleRow + PADDLE_HEIGHT)) || ((ballRow + BALL_SIDE_LENGTH) >= paddleRow)){
				////ball is in valid row
				//
				//return true;
			////}
		//}
	//}
	//
	//return false;
	if (ballRow != 0x00 || ballRow != 0x01 || ballRow != 0x10 || ballRow != 0x11 )
		return false;
	
		if ((ballCol <= (paddleCol + PADDLE_WIDTH) && ((ballCol + BALL_SIDE_LENGTH) >= paddleCol))){
			if (paddleRow == 0){
			
				if (ballRow == 0x10 || ballRow == 0x11){
					return false;
				}
			} else {
				if (ballRow = 0x00 || ballRow ==  0x01){
					return false;
				}
			}
	}
		return true;
}

void PlayerOneScored(){
		BallCol = 0x03;
		BallRow = 0x05;
	
}


void PlayerTwoScored(){
	BallCol = 0x05;
	BallRow = 0x03;
}


void RedrawScreen(){
	
	
	
	SetPlayerOnePaddleCol(PlayerOnePaddleCol);
	SetPlayerTwoPaddleCol(PlayerTwoPaddleCol);
	
	if (BallCol > 27){
		//BallCol = 0;
		BallGoingRight = !BallGoingRight;
	}
	
	if (BallRow > 20){
		BallGoingDown = !BallGoingDown;
		//BallRow = 0;
	}
	SetBallCol(BallCol);
	SetBallRow(BallRow);
	
}

void UpdateFrame(){
	
	
	//determine if ball is colliding
	
	//check left wall collision
	if (BallCol == 0x00){
		BallGoingRight = !BallGoingRight;
	}
	
	//check right wall collision
	if (BallCol >= 0x1B){
		BallGoingRight = !BallGoingRight;
	}
	
	
	//debug
	p1CollisionOccuring = Collision(PlayerOnePaddleCol, 0, BallRow, BallCol);
	p2CollisionOccuring = Collision(PlayerTwoPaddleCol, 20, BallRow, BallCol);
	
	//check player 1 paddle collision
	if (Collision(PlayerOnePaddleCol, 0, BallRow, BallCol)){
		//collision has occurred
		
		//reverse ball direction
		BallGoingDown = !BallGoingDown;
		
	}
	
	
	//check player 2 paddle collision
	if (Collision(PlayerTwoPaddleCol, 20, BallRow, BallCol)){
		//collision has occurred
		
		//reverse ball direction
		BallGoingDown = !BallGoingDown;
	}
	
	//collision has not occurred, it is possible that a point has been scored
	
	//point scored on player one
	if (PointScored(PlayerOnePaddleCol, 0, BallRow, BallCol)){
		//Therefore PlayerTwo has Scored
		
		//BallGoingDown = !BallGoingDown;
		PlayerTwoScored();
	}
	
	//point scored on player two
	if (PointScored(PlayerTwoPaddleCol, 20, BallRow, BallCol)){
		//therefore Player One has scored
		//BallGoingDown = !BallGoingDown;
		PlayerOneScored();
	}
	
	//no collisions have been detected and no points have been scored 
	//move paddles accordingly
	
	//set player one paddle position
	//use bitmask
	switch (PlayerOneUSARTData & 0x0F) {
		case 0x00:
			PlayerOnePaddleCol = 0x00;
			break;
		case 0x01:
			PlayerOnePaddleCol = 0x02;
			break;
		case 0x02:
			PlayerOnePaddleCol = 0x04;
			break;
		case 0x03:
			PlayerOnePaddleCol = 0x06;
			break;
		case 0x04:
			PlayerOnePaddleCol = 0x08;
			break;
		case 0x05:
			PlayerOnePaddleCol = 0x0A;
			break;
		case 0x06:
			PlayerOnePaddleCol = 0x0C;
			break;
		case 0x07:
			PlayerOnePaddleCol = 0x0E;
			break;
		case 0x08:
			PlayerOnePaddleCol = 0x10;
			break;
		case 0x09:
			PlayerOnePaddleCol = 0x12;
			break;
		case 0x0A:
			PlayerOnePaddleCol = 0x14;
			break;
		default:
			break;
		
	}

	//set player two paddle position
	switch (PlayerTwoUSARTData & 0x0F)
	{
		case 0x00:
			PlayerTwoPaddleCol = 0x00;
			break;
		case 0x01:
			PlayerTwoPaddleCol = 0x02;
			break;
		case 0x02:
			PlayerTwoPaddleCol = 0x04;
			break;
		case 0x03:
			PlayerTwoPaddleCol = 0x06;
			break;
		case 0x04:
			PlayerTwoPaddleCol = 0x08;
			break;
		case 0x05:
			PlayerTwoPaddleCol = 0x0A;
			break;
		case 0x06:
			PlayerTwoPaddleCol = 0x0C;
			break;
		case 0x07:
			PlayerTwoPaddleCol = 0x0E;
			break;
		case 0x08:
			PlayerTwoPaddleCol = 0x10;
			break;
		case 0x09:
			PlayerTwoPaddleCol = 0x12;
			break;
		case 0x0A:
			PlayerTwoPaddleCol = 0x14;
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
	while (1){
		UpdateFrame();
		_delay_ms(150);
	}
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
			
			_delay_ms(60);
			
//set player one paddle position
	//use bitmask
	switch (PlayerOneUSARTData & 0x0F) {
		case 0x00:
			PlayerOnePaddleCol = 0x00;
			break;
		case 0x01:
			PlayerOnePaddleCol = 0x02;
			break;
		case 0x02:
			PlayerOnePaddleCol = 0x04;
			break;
		case 0x03:
			PlayerOnePaddleCol = 0x06;
			break;
		case 0x04:
			PlayerOnePaddleCol = 0x08;
			break;
		case 0x05:
			PlayerOnePaddleCol = 0x0A;
			break;
		case 0x06:
			PlayerOnePaddleCol = 0x0C;
			break;
		case 0x07:
			PlayerOnePaddleCol = 0x0E;
			break;
		case 0x08:
			PlayerOnePaddleCol = 0x10;
			break;
		case 0x09:
			PlayerOnePaddleCol = 0x12;
			break;
		case 0x0A:
			PlayerOnePaddleCol = 0x14;
			break;
		default:
			break;
		
	}

	//set player two paddle position
	switch (PlayerTwoUSARTData & 0x0F)
	{
		case 0x00:
			PlayerTwoPaddleCol = 0x00;
			break;
		case 0x01:
			PlayerTwoPaddleCol = 0x02;
			break;
		case 0x02:
			PlayerTwoPaddleCol = 0x04;
			break;
		case 0x03:
			PlayerTwoPaddleCol = 0x06;
			break;
		case 0x04:
			PlayerTwoPaddleCol = 0x08;
			break;
		case 0x05:
			PlayerTwoPaddleCol = 0x0A;
			break;
		case 0x06:
			PlayerTwoPaddleCol = 0x0C;
			break;
		case 0x07:
			PlayerTwoPaddleCol = 0x0E;
			break;
		case 0x08:
			PlayerTwoPaddleCol = 0x10;
			break;
		case 0x09:
			PlayerTwoPaddleCol = 0x12;
			break;
		case 0x0A:
			PlayerTwoPaddleCol = 0x14;
			break;
		default:
			break;
		
	}
		}
	}
	
	
}



#endif /* PONG_H_ */