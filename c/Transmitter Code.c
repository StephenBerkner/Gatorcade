/*
 * MCP_Controller.c
 *
 * Created: 9/13/2019 12:54:49 PM
 * Author : Anthony Dermody
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include "I2C.h"
#define BAUD 2400
#define MYUBRR ((F_CPU/(16UL*BAUD))-1)
volatile uint8_t A;
volatile uint8_t A_button;
volatile uint8_t A_joystick;
volatile uint8_t button;
volatile uint8_t joystickH;
volatile uint8_t joystickV;
volatile uint8_t yo;
volatile uint8_t baudrate;
volatile uint8_t uartreg;
volatile uint8_t value; 
volatile uint8_t X;
volatile uint8_t Y;
volatile uint8_t Z;
volatile uint16_t XH_temp;
volatile uint16_t YH_temp;
volatile uint16_t ZH_temp;
volatile int GyroX;
volatile int GyroY;
volatile int GyroZ;
volatile int GyroXg;
volatile int GyroYg;
void adc_init(void) {
	//ADMUX |=  (1 << REFS1) | (1 << REFS0) | (1 << MUX0);
	//ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADFR);
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	//ADMUX |= (1 << REFS1) | (1 << REFS0);
	//ADMUX |= (1 << ADLAR);
	// ADCSRB = 0x00;
	ADCSRA |= (1 << ADATE);
	ADCSRB |= 0x00;
	
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADSC);
}
void adc_readV(void) {
	joystickV = 0;
	ADMUX = 0b11000001;
	_delay_ms(5);
	joystickV = ADC;
	//yo = ADC;
}
void adc_readH(void) {
	joystickH = 0;
	ADMUX = 0b11000000;
	_delay_ms(5);
	joystickH = ADC;
}
 void i2c_init(){

	 DDRC |= (1<< PORTC0) | (1 << PORTC1);
	 TWBR=0x02;    // Bit rate
	 // SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
	 TWCR |= (1<<TWEN);
	 TWSR = 0x00;    // Setting prescalar bits to 1


 }

 void i2c_start(){

	 // Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	 TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	 while(!(TWCR & (1<<TWINT))); // Wait till start condition is transmitted
	 //while((TWSR & 0xF8)!= 0x08); // Check for the acknowledgement


 }

 void i2c_stop(){

	 // Clear TWI interrupt flag, Put stop condition on SDA, Enable TWI
	 TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	 while(!(TWCR & (1<<TWSTO)));  // Wait till stop condition is transmitted

 }

 void i2c_write_address(uint8_t input){

	 TWDR = input;    // Address and read instruction
	 TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	 while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
	 //while((TWSR & 0xF8)!= 0x18);  // Check for the acknoledgement

 }

 void i2c_read_address(uint8_t input){

	 TWDR = input;    // Address and read instruction
	 TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	 while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
	 //    while((TWSR & 0xF8)!= 0x40);  // Check for the acknoledgement

 }
 void i2c_write_data(uint8_t input){

	 TWDR = input;    // Address and read instruction
	 TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	 while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
	 //while((TWSR & 0xF8)!= 0x28);  // Check for the acknoledgement

 }
 uint8_t i2c_read(int ack){

	 if(ack == 0){
		 TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
		 while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
		 while((TWSR & 0xF8) != 0x58); // Check for the acknoledgement
		 }else{
		 TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);    // Clear TWI interrupt flag,Enable TWI
		 while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
		 //while((TWSR & 0xF8) != 0x50); // Check for the acknoledgement
		 
	 }
	 return TWDR;
	 
 }


 uint8_t ReadRegisterSingleByte(uint8_t deviceAddress, uint8_t registerAddress){
	 uint8_t toReturn = 0x00;
	 
	 i2c_start();
	 i2c_write_address(deviceAddress << 1);

	 i2c_write_data(registerAddress);
	 
	 //i2c_stop();
	 i2c_start();
	 
	 i2c_read_address((deviceAddress << 1) | 0x01);
	 toReturn = i2c_read(0);
	 i2c_stop();

	 return toReturn;
 }

 uint16_t ReadRegisterMultipleBytes(uint8_t deviceAddress, uint8_t MSBAddress, uint8_t LSBAddress){
	 uint16_t toReturn = 0x0000;
	 
	 //get MSB
	 i2c_start();
	 i2c_write_address(deviceAddress << 1);

	 i2c_write_data(MSBAddress);
	 
	 i2c_start();
	 
	 i2c_read_address((deviceAddress << 1) | 0x01);
	 toReturn = i2c_read(0) << 8;
	 i2c_stop();
	 
	 //get LSB
	 i2c_start();
	 i2c_write_address(deviceAddress << 1);

	 i2c_write_data(LSBAddress);
	 
	 i2c_start();
	 
	 i2c_read_address((deviceAddress << 1) | 0x01);
	 toReturn |= i2c_read(0);
	 i2c_stop();
	 
	 return toReturn;
	 
	 
 }
void gyro_init(void) {
	//_delay_ms(150);	
	i2c_start();
	i2c_write_address(0x68 << 1);
	i2c_write_address(0x19);
	i2c_write_data(0x07);
	//value = ReadRegisterSingleByte(0x68, 0x19);
	i2c_stop();
	
	i2c_start();
	i2c_write_address(0x68 << 1);
	i2c_write_address(0x6B);
	i2c_write_data(0x01);
	i2c_stop();

	i2c_start();
	i2c_write_address(0x68 << 1);
	i2c_write_address(0x1A);
	i2c_write_data(0x00);
	i2c_stop();
	
	i2c_start();
	i2c_write_address(0x68 << 1);
	i2c_write_address(0x1B);
	i2c_write_data(0x18);
	i2c_stop();

	i2c_start();
	i2c_write_address(0x68 << 1);
	i2c_write_address(0x1C);
	i2c_write_data(0x18);
	i2c_stop();
}
void io_init(void) {
	//DDRA |= 0xFF;
	DDRB |= 0xFE;
	};

void MPU_start_loc(void) {
	i2c_write_address(0x68);
}

void uart_init(void) {
		UCSR0C |= (0 << UMSEL00) | (0 << UMSEL01);
		UBRR0H = (unsigned int)(MYUBRR>>8);
		UBRR0L = (unsigned int) MYUBRR;
		DDRD |= 0b00000110;
		UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
		UCSR0C |= (1 <<UCSZ00) | (1 << UCSZ01);
		UCSR0B|=(1<<RXCIE0) | (1 << TXCIE0);
		sei(); 
}

uint8_t uart_receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}
uint8_t uart_transmit(uint8_t data) {
	  while((UCSR0A & (1<<UDRE0)) == 0);

	  // Transmit data
	  UDR0 = data;
}
ISR(USART0_RX_vect) {
		uartreg = uart_receive();
		PORTB = uartreg;
//		_delay_ms(1000);
}

int main(void)
{
    /* Replace with your application code */
	io_init();
	adc_init();
	i2c_init();
	uart_init();
	gyro_init();
    while (1) 
    {
		//	PORTA = 0x00;
		button = PINB & (0b00000001);
		adc_readV();
		adc_readH();
		value = ReadRegisterSingleByte(0x68, 0x75);
// 		i2c_start();
// 		i2c_write_address(0x68 << 1);
// 		i2c_write_address(0x19);
// 		i2c_write_data(0x07);
// 		i2c_stop();
		X = ReadRegisterSingleByte(0x68, 0x3C);
		XH_temp = ReadRegisterSingleByte(0x68, 0x3B);
		XH_temp = (XH_temp << 8);
		GyroX = XH_temp | X;
		
		Y = ReadRegisterSingleByte(0x68, 0x3E);
		YH_temp = ReadRegisterSingleByte(0x68, 0x3D);
		YH_temp = (YH_temp << 8);
		GyroY = YH_temp | Y;

		Z = ReadRegisterSingleByte(0x68, 0x40);
		ZH_temp = ReadRegisterSingleByte(0x68, 0x3F);
		ZH_temp = (ZH_temp << 8);
		GyroZ = ZH_temp | Z;

// 		if (GyroY < -1500) {
// 			A = 0b10000000;
// 			//uart_transmit(0b10000000);
			//	A = 0b011;
// 		}


			//-3
		if (GyroY < -1800) {
			//paddle0
			A= 0b00000000;
		}
		 else if (GyroY < -1500) {
			//A = 0b11000000;
			//uart_transmit(0b10000000);
			//A= 0b011;
			//paddle1
			A = 0b00000001;
		}
			//-2
		else if (GyroY < -900) {
	//		PORTA = 0b00100000;
			//A =  0b01100000;
			//A = 0b010;
			//paddle2
			A = 0b00000010;
		}
		else if (GyroY < -500) {
			//A =  0b00110000;
			//A= 0b001
			//paddle3
			A = 0b00000011;
		}
			//-1
		else if (GyroY < -100) {
			//A =  0b00110000;
			//A= 0b001
			//paddle4
			A = 0b00000100;
		}

		 if (GyroY > -99 && GyroY < 99) {
			//A = 0b00011000;
			//paddle5
			A = 0b00000101;
			//uart_transmit(0b00001000);
		}
		if (GyroY > 100) {
		//A = 0b00001100;
			//uart_transmit(0b00000100);
			//paddle6
			//A=0b100;
			A = 0b00000110;
		}
		
		if (GyroY > 500) {
		//A = 0b00001100;
			//uart_transmit(0b00000100);
			//paddle7
			//A=0b100;
			A = 0b00000111;
		}
		if (GyroY > 1000) {
			//A = 0b00000110;
			//uart_transmit(0b00000001);
			//A=0b101;
			//Paddle8
			A = 0b00001000;
			
		}
		if (GyroY > 1500) {
			//A = 0b00000011;
			//uart_transmit(0b00000001);
			//A=0b110;
			//paddle9
			A = 0b00001001;
		}
		if (GyroY > 1800) {
			//A = 0b00000011;
			//uart_transmit(0b00000001);
			//A=0b110;
			//paddle10
			A = 0b00001010;
		}
		if(joystickH >200) {
			//PORTB = 0x02;
			A_joystick = 0x70;
		
			
		}
		else if(joystickV > 200) {
			//PORTB = 0x04;
			A_joystick = 0x30;

		}
		else if (button == 0x00) {
						//PORTB = 0x08
						A_button = 0x80;
					}
		
		else {
			//PORTB = 0x00;
			A_button = 0x00;
			A_joystick = 0x00;
		}
		A =  A_button | A_joystick | A;
// 		if(button == 0x00) {
// 			PORTB = 0x08;
// 		}
// 		if (button == 0x01) {
// 			PORTB = 0x00;
// 		}
		uart_transmit(A);
//		joystick = ADC;

	
		
    }
}

