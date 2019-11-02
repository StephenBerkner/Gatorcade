/*
 * Magnetometer.h
 *
 * Created: 9/10/2019 3:06:15 PM
 *  Author: sberk
 * Magnetometer include file for BMM150 Magnetometer
 * https://www.mouser.com/datasheet/2/783/BST-BMM150-DS001-01-786480.pdf
 */ 

/*
#ifndef MAGNETOMETER_H_
#define MAGNETOMETER_H_

#include "I2C.h"
#include "LCD.h"

#define NUM_MAGNETOMETERS	5
#define TOLERANCE			150



struct Magnetometer {
	//x, y, and z axis readings
	//x and y are 12-bit values
	int16_t xData;
	int16_t yData;
	
	//z is a 14-bit value
	int16_t zData;
	
	//calibrated values are also needed in order
	//to determine when motion occurs
	int16_t calibratedXData;
	int16_t calibratedYData;
	int16_t calibratedZData;
	
	//this should be a value between 1 and the number of magnetometers
	uint8_t position;

};

//array to contains all the magnetometer structs
volatile Magnetometer Magnetometers[NUM_MAGNETOMETERS];


//use this function as a constructor
//ensures all data types are initialized appropriately
Magnetometer * NewMagnetometer(uint8_t position){
	if (position > NUM_MAGNETOMETERS || position < 0 )
		return NULL;
		
	Magnetometer * toReturn = new Magnetometer;
	
	toReturn->xData = 0;
	toReturn->yData = 0;
	toReturn->zData = 0;
	
	toReturn->position = position;
	
	
}

//most significant 4 bits correspond to which magnetometer it is
//0b0001 is magnetometer 1, 0b0010 is magnetometer 2, etc.
//least significant 4 bits correspond to the axis of detected motion
//0b0001 is x axis, 0b0010 is y axis, 0b0011 is z axis
//a return value of 0x00 means no motion was detected

uint8_t GetMagnetPosition(){
	
	uint8_t toReturn = 0x00;
	
	//for determining the axis of detection
	char axis;
	
	//loop over array of magnetometers
	for (uint8_t index = 0x01; index < NUM_MAGNETOMETERS; index++){
		
		if ((axis = MotionDetected(Magnetometers[index])) != 0x00){
			
			if (axis == 'x'){
				toReturn |= 0x01 << 4;
				toReturn |= index;	
			
			} else if (axis == 'y'){
				toReturn |= 0x02 << 4;
				toReturn |= index;
								
			} else if (axis == 'z'){
			
				toReturn |= 0x03 << 4;
				toReturn |= index;				
			}		
		}
	}	
	
}


/*
* This function returns either the character x, y, or z
* if motion is detected in one of those axises. Otherwise
* 0x00 will be returned which is false.
*/

/*
char MotionDetected(Magnetometer mag){
	//check x axis first
	if (mag.xData > mag.calibratedXData + TOLERANCE || mag.xData < mag.calibratedXData - TOLERANCE )
		return 'x';
	
	//check y axis second
	if (mag.yData > mag.calibratedYData + TOLERANCE || mag.yData < mag.calibratedYData - TOLERANCE )
		return 'y';
	
	//check z axis third
	if (mag.zData > mag.calibratedZData + TOLERANCE || mag.zData < mag.calibratedZData - TOLERANCE )
		return 'z';
		
	//if no motion is detected return 0x00 which is false
	return 0x00;
	
}

/*
Magnetometer calibration, read and write code

volatile uint8_t value;
unsigned char data;
unsigned char SPITransmitting;
volatile uint8_t MagXL =0; //Initialize Accelerometer X, Y, and Z registers
volatile uint8_t MagXH =0;
volatile uint8_t MagYL =0;
volatile uint8_t MagYH =0;
volatile uint8_t MagZL =0;
volatile int8_t MagZH =0;
volatile int16_t MagXMSB = 0;
volatile int16_t MagYMSB = 0;
volatile int16_t MagZMSB = 0;
volatile int16_t MagX = 0;
volatile int16_t MagY = 0;
volatile int16_t MagZ = 0;
volatile int16_t MagXLCD = 0;
volatile int16_t MagYLCD = 0;
volatile int16_t MagZLCD = 0;
volatile uint8_t datardy;
char magnetoLCD[8];

void spi_init(void) {
	DDRB |= (1<<DDB5)|(1<<DDB7) | (1<<DDB4)| (0 << DDB6);
	//SPSR0 |= (1<<SPI2X0);
	SPCR |= (1<<SPE)|(1<<MSTR)| (1 << SPR0) | (0 << SPR1) ;
	//PORTB = (1<<DDB4);
}
void io_init(void) {
	DDRA |= (1 << DDA0);
	//DDRD |= (1 << DDD0) | (1 << DD)
}
uint8_t spi_write(uint8_t data) {
	uint8_t LSB;
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	//LSB = SPDR;
	return SPDR;
	
}
uint8_t spi_read(void){
	return spi_write(0x37);
}



void mag_write(uint8_t reg_addr, uint8_t data) {
	PORTA &= 0b11111110; //Set SSA to active low to enable slave select
	reg_addr = (0b01111111 & reg_addr);//Set MSB to low to write
	uint8_t trash = spi_write(reg_addr); //When initially writing, first value will be trash data and must not be accounted for
	trash = spi_write(data);
	PORTA |= 0b00000001; //Set SSA to active high to disable slave select
}
uint8_t mag_read(uint8_t reg_addr) {
	//uint8_t add = 0b00111111 & reg_addr;
	PORTA &= 0b11111110; //Set SSA to active low to enable slave select
	uint8_t regaddr = 0b10000000|reg_addr;// Set MSB to high to read
	spi_write(regaddr); //Write from desired register address
	uint8_t data = spi_read(); //Read from desired regaddress
	PORTA |= 0b00000001; //Set SSA to active high to disable slave select
	return data;
}
void mag_init(void){
	mag_write(0x4B, 0x01); //Power Ctrl Bit
	_delay_ms(10);
	mag_write(0x4B, 0x83); //perform soft reset which puts device in sleep mode
	_delay_ms(10);
	mag_write(0x4B, 0x05); // SPI 3-wire Mode and power ctrl bit enabled
	_delay_ms(10);
	mag_write(0x4C, 0x28); // 20HZ Output Data Rate
	_delay_ms(10);
	mag_write(0x51, 0xFF); // Max repititons for X/Y readings
	_delay_ms(10);
	mag_write(0x52, 0xFF); // Max reptitions for Z readings
}

int main(void)
{
	io_init();
	lcd_init();
	spi_init();
	mag_init();

	while (1)
	{
		///////////////////////////////////////////// Initial MagX/Y/Z Readings
		datardy = mag_read(0x48);
		datardy &= 0b00000001;
		if (datardy == 0x01) {
			MagXL = mag_read(0x42);
			MagXH = mag_read(0x43);
			MagXMSB =  ((int16_t)((int8_t) MagXH)) * 32;
			MagX = (int16_t)(MagXMSB | MagXL);

			MagYL = mag_read(0x44);
			MagYH = mag_read(0x45);
			MagYMSB =  ((int16_t)((int8_t) MagYH)) * 32;
			MagY = (int16_t)(MagYMSB | MagYL);

			MagZL = mag_read(0x46);
			MagZH = mag_read(0x47);
			MagZMSB =  ((int16_t)((int8_t) MagZH)) * 128;
			MagZ = (int16_t)(MagZMSB | MagZL);
			/////////////////////////////////////////////////////////// Output MagX to LCD
			MagXLCD = MagX;
			//value = mag_read(0x4C);
			if(MagXLCD > 0) {
				MagXLCD = MagXLCD;
				magnetoLCD[6] = '0';
				} else {
				MagXLCD = ~MagXLCD +0b1;
				magnetoLCD[6] = '-';
			}
			for(int k = 0; k < 6; k++) {
				int d1 = fmod(MagXLCD,10);
				char c = d1 + '0';
				magnetoLCD[k] = c;
				MagXLCD = MagXLCD/10;
			}
			for(int j = 6; j >= 0; j--) {
				lcd_char(magnetoLCD[j]);
			}
			//lcd_command(0xC0);
			/////////////////////////////////////////////////////// Output MagY To LCD
			MagYLCD = MagY;
			if(MagYLCD > 0) {
				MagYLCD = MagYLCD;
				magnetoLCD[6] = '0';
				} else {
				MagYLCD = ~MagYLCD +0b1;
				magnetoLCD[6] = '-';
			}
			for(int k = 0; k < 6; k++) {
				int d1 = fmod(MagYLCD,10);
				char c = d1 + '0';
				magnetoLCD[k] = c;
				MagYLCD = MagYLCD/10;
			}
			for(int j = 6; j >= 0; j--) {
				lcd_char(magnetoLCD[j]);
			}
			lcd_command(0xC0);
			///////////////////////////////////////////////////Output MagZ to LCD
			MagZLCD = MagZ;
			if(MagZLCD > 0) {
				MagZLCD = MagZLCD;
				magnetoLCD[6] = '0';
				} else {
				MagZLCD = ~MagZLCD +0b1;
				magnetoLCD[6] = '-';
			}
			for(int k = 0; k < 6; k++) {
				int d1 = fmod(MagZLCD,10);
				char c = d1 + '0';
				magnetoLCD[k] = c;
				MagZLCD = MagZLCD/10;
			}
			for(int j = 6; j >= 0; j--) {
				lcd_char(magnetoLCD[j]);
			}
			lcd_command(0x02);
		}
		value = mag_read(0x51); // Read to ensure registers are writing correctly
	}
}



*/


//#endif /* MAGNETOMETER_H_ */