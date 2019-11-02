/*
 * LEDMatrix.h
 *
 * Created: 9/23/2019 10:07:47 PM
 *  Author: sberk
 */ 


#ifndef LEDMATRIX_H_
#define LEDMATRIX_H_

#define HEIGHT 32
#define WIDTH 32

LED Matrix [WIDTH][HEIGHT];



struct LED {
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
	
};

LED* CreateLED(){
	LED * toReturn = malloc(sizeof LED);
	toReturn->Red = 0x00;
	toReturn->Blue = 0x00;
	toReturn->Green = 0x00;
}

//populate matrix with LED structs
void MatrixInit(){
	for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDTH; j++){
			Matrix[i][j] = CreateLED();
		}
	}
}

void MatrixToBlack(){
	for (int row = 0; row < HEIGHT; row++){
		for (int col = 0; col < WIDTH; col++){
			ToBlack(Matrix[row][col]);
		}
	}
	
}

//color methods
void ToBlack(LED * pixel){
	pixel->Red = 0x00;
	pixel->Green = 0x00;
	pixel->Blue = 0x00;
}

void ToWhite(LED * pixel){
	pixel->Red = 0xFF;
	pixel->Green = 0xFF;
	pixel->Blue = 0xFF;
}

void ToRed(LED * pixel){
	pixel->Red = 0xFF;
	pixel->Green = 0x00;
	pixel->Blue = 0x00;
}

void ToGreen(LED * pixel){
	pixel->Red = 0x00;
	pixel->Green = 0xFF;
	pixel->Blue = 0x00;
}

void ToBlue(LED * pixel){
	pixel->Red = 0x00;
	pixel->Green = 0x00;
	pixel->Blue = 0xFF;
}







#endif /* LEDMATRIX_H_ */