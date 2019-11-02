/*
 * Master.c
 *
 * Created: 8/25/2019 11:52:37 PM
 * Author : sberk
 */ 

#include <avr/io.h>
#include <util/delay.h>
//#include "Magnetometer.h"

//#include "MPU6050.h"
//
//uint8_t WHO_AM_I = 0x00;
//uint8_t check = 0x00;
//
//uint16_t XAccelData = 0x0000;
//uint16_t YAccelData = 0x0000;
//uint16_t ZAccelData = 0x0000;
//
//uint16_t XGyroData = 0x0000;
//uint16_t YGyroData = 0x0000;
//uint16_t ZGyroData = 0x0000;

#include "Pong.h"
#include "USART.h"

int main(void)
{
	
	PongInit();
	USARTInit();
	
	DDRB |= 0x01;
	PORTB = 0x01;
    
	_delay_ms(300);
	PORTB = 0x00;
	while (1) 
    {
		StartupTest();
		//PORTC |= 0b00000100;
	
		USARTDataReceived = USARTReceive();
		USARTTransmit(0xAA);
		if (USARTDataReceived == 0xFF){
			PORTB = 0x01;
			_delay_ms(2000);
		}
    }
}

