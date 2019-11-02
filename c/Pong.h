/*
 * Pong.h
 *
 * Created: 9/23/2019 10:06:56 PM
 *  Author: sberk
 */ 


#ifndef PONG_H_
#define PONG_H_
#include <stdbool.h>

//#include "LEDMatrix.h"

#define PADDLE_WIDTH		6
#define PADDLE_HEIGHT		2

#define PLAYER_ONE_PADDLE_ROW 21
#define PLAYER_TWO_PADDLE_ROW 5

#define BALL_SIDE_LENGTH	2


//board constants 0->constant
#define NUM_BALL_COLS 17
#define NUM_BALL_ROWS 27


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

void PongInit(){
	
	//PlayerOnePaddleRow =  //(HEIGHT + PADDLE_HEIGHT) / 2;
	PlayerOnePaddleCol = 0;//PADDLE_BORDER;
	PlayerOnePaddleSpeed = 0;
	
	//PlayerTwoPaddleRow = (HEIGHT + PADDLE_HEIGHT) / 2;
	PlayerTwoPaddleCol = 0;// (WIDTH/2) - PADDLE_BORDER;
	PlayerTwoPaddleSpeed = 0;
	
	//place ball in player one's area
	//change this to random or something more complex later
	BallRow = 0;// (HEIGHT + BALL_SIDE_LENGTH) / 2;
	BallCol = 0;//WIDTH / 4 + BALL_SIDE_LENGTH / 2;
	
	//port inits
	//set first 5 pins as output pins
	
	//paddle 1
	DDRA = 0x1F;
	PORTA = 0x00;
	
	//paddle 2
	DDRB = 0x1F;
	PORTB = 0x00;
	
	//Ball Row
	DDRC = 0x1F;
	PORTC = 0x00;
	
	//Ball Col
	DDRD = 0x1F;
	PORTD = 0x00;
	
}


//set Player 1 paddle column
void SetPlayerOnePaddleCol(uint8_t col){
	switch (col){
		case 0:
			PORTA = 0x00;
			break;
		case 1:
			PORTA = 0x01;
			break;
		case 2:
			PORTA = 0x02;
			break;
		case 3:
			PORTA = 0x03;
			break;
		case 4:
			PORTA = 0x04;
			break;
		case 5:
			PORTA = 0x05;
			break;
		case 6:
			PORTA = 0x06;
			break;
		case 7:
			PORTA = 0x07;
			break;
		case 8:
			PORTA = 0x08;
			break;
		case 9:
			PORTA = 0x09;
			break;
		case 10:
			PORTA = 0x0A;
			break;
		case 11:
			PORTA = 0x0B;
			break;
		case 12:
			PORTA = 0x0C;
			break;
		case 13:
			PORTA = 0x0D;
			break;
		case 14:
			PORTA = 0x0E;
			break;
		case 15:
			PORTA = 0x0F;
			break;
		case 16:
			PORTA = 0x10;
			break;
		case 17:
			PORTA = 0x11;
			break;
		case 18:
			PORTA = 0x12;
			break;
		case 19:
			PORTA = 0x13;
			break;
		case 20:
			PORTA = 0x14;
			break;
		case 21:
			PORTA = 0x15;
			break;
		case 22:
			PORTA = 0x16;
			break;
		case 23:
			PORTA = 0x17;
			break;
		case 24:
			PORTA = 0x18;
			break;
		case 25:
			PORTA = 0x19;
			break;	
		case 26:
			PORTA = 0x1A;
			break;
		default:
			break;
		
	}
}


//set Player 2 paddle column
void SetPlayerTwoPaddleCol(uint8_t col){
	switch (col){
		case 0:
			PORTB = 0x00;
			break;
		case 1:
			PORTB = 0x01;
			break;
		case 2:
			PORTB = 0x02;
			break;
		case 3:
			PORTB = 0x03;
			break;
		case 4:
			PORTB = 0x04;
			break;
		case 5:
			PORTB = 0x05;
			break;
		case 6:
			PORTB = 0x06;
			break;
		case 7:
			PORTB = 0x07;
			break;
		case 8:
			PORTB = 0x08;
			break;
		case 9:
			PORTB = 0x09;
			break;
		case 10:
			PORTB = 0x0A;
			break;
		case 11:
			PORTB = 0x0B;
			break;
		case 12:
			PORTB = 0x0C;
			break;
		case 13:
			PORTB = 0x0D;
			break;
		case 14:
			PORTB = 0x0E;
			break;
		case 15:
			PORTB = 0x0F;
			break;
		case 16:
			PORTB = 0x10;
			break;
		case 17:
			PORTB = 0x11;
			break;
		case 18:
			PORTB = 0x12;
			break;
		case 19:
			PORTB = 0x13;
			break;
		case 20:
			PORTB = 0x14;
			break;
		case 21:
			PORTB = 0x15;
			break;
		case 22:
			PORTB = 0x16;
			break;
		case 23:
			PORTB = 0x17;
			break;
		case 24:
			PORTB = 0x18;
			break;
		case 25:
			PORTB = 0x19;
			break;
		case 26:
			PORTB = 0x1A;
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
			PORTC = 0x00;
			break;
		case 1:
			PORTC = 0x01;
			break;
		case 2:
			PORTC = 0x02;
			break;
		case 3:
			PORTC = 0x03;
			break;
		case 4:
			PORTC = 0x04;
			break;
		case 5:
			PORTC = 0x05;
			break;
		case 6:
			PORTC = 0x06;
			break;
		case 7:
			PORTC = 0x07;
			break;
		case 8:
			PORTC = 0x08;
			break;
		case 9:
			PORTC = 0x09;
			break;
		case 10:
			PORTC = 0x0A;
			break;
		case 11:
			PORTC = 0x0B;
			break;
		case 12:
			PORTC = 0x0C;
			break;
		case 13:
			PORTC = 0x0D;
			break;
		case 14:
			PORTC = 0x0E;
			break;
		case 15:
			PORTC = 0x0F;
			break;
		case 16:
			PORTC = 0x10;
			break;
		case 17:
			PORTC = 0x11;
			break;
		case 18:
			PORTC = 0x12;
			break;
		case 19:
			PORTC = 0x13;
			break;
		case 20:
			PORTC = 0x14;
			break;
		case 21:
			PORTC = 0x15;
			break;
		case 22:
			PORTC = 0x16;
			break;
		case 23:
			PORTC = 0x17;
			break;
		case 24:
			PORTC = 0x18;
			break;
		case 25:
			PORTC = 0x19;
			break;
		case 26:
			PORTC = 0x1A;
			break;
		case 27:
			PORTC = 0x1B;
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
			PORTD = 0x00;
			break;
		case 1:
			PORTD = 0x01;
			break;
		case 2:
			PORTD = 0x02;
			break;
		case 3:
			PORTD = 0x03;
			break;
		case 4:
			PORTD = 0x04;
			break;
		case 5:
			PORTD = 0x05;
			break;
		case 6:
			PORTD = 0x06;
			break;
		case 7:
			PORTD = 0x07;
			break;
		case 8:
			PORTD = 0x08;
			break;
		case 9:
			PORTD = 0x09;
			break;
		case 10:
			PORTD = 0x0A;
			break;
		case 11:
			PORTD = 0x0B;
			break;
		case 12:
			PORTD = 0x0C;
			break;
		case 13:
			PORTD = 0x0D;
			break;
		case 14:
			PORTD = 0x0E;
			break;
		case 15:
			PORTD = 0x0F;
			break;
		case 16:
			PORTD = 0x10;
			break;
		case 17:
			PORTD = 0x11;
			break;
		default:
			break;
		
			}
}

bool CollisionCheck(uint8_t paddleCol, uint8_t paddleRow, uint8_t ballRow, uint8_t ballCol){
	//ball is in the middle of the board
	if (ballRow > 5 || ballRow < 21)
		return false;
	
	//check columns
	//if ball is outside of paddle
	if ((ballCol > (paddleCol + PADDLE_WIDTH) || ((ballCol + BALL_SIDE_LENGTH) < paddleCol)))
		return false;
	
	//check rows
	//if ball is outside of paddle row
	if ((ballRow > (paddleRow + PADDLE_HEIGHT)) || ((ballRow + BALL_SIDE_LENGTH) < paddleRow))
		return false;
	
	//ball must be colliding
	return true;
	
	
	
}

bool PointScored(uint8_t paddleCol, uint8_t paddleRow, uint8_t ballRow, uint8_t ballCol){
	
	
}



void UpdateFrame(){
	
	if (PlayerOneGoingRight){
		PlayerOnePaddleCol += PlayerOnePaddleSpeed;	
	} else {
		PlayerOnePaddleCol -= PlayerOnePaddleSpeed;	
	}
	
	if (PlayerTwoGoingRight){
		PlayerTwoPaddleCol += PlayerTwoPaddleSpeed;	
	} else {
		PlayerTwoPaddleCol -= PlayerTwoPaddleSpeed;
	}
	
	if (BallGoingDown){
		BallRow += BallYSpeed;	
	} else {
		BallRow -= BallYSpeed;
	}
	
	if (BallGoingRight){
		BallCol += BallXSpeed;
			
	} else {
		BallCol -= BallXSpeed;
	}
	
	RedrawScreen();
	
}


void RedrawScreen(){
	//reset matrix before drawing appropriate items
	//MatrixToBlack();
	
	SetPlayerOnePaddleCol(PlayerOnePaddleCol);
	SetPlayerTwoPaddleCol(PlayerTwoPaddleCol);
	
	SetBallCol(BallCol);
	SetBallRow(BallRow);
	
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
			
			//configure player one paddle
			//SetPlayerOnePaddleCol(col);
			//
			////configure player two paddle
			//SetPlayerTwoPaddleCol(col);
			//_delay_ms(1000);
		}
	}
}



#endif /* PONG_H_ */