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
volatile uint8_t B;
volatile uint8_t B_button;
volatile uint8_t B_joystick;
volatile int ball = 0;
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
volatile int menu;
volatile int pong_on = 0;
volatile int stack_on = 0;
volatile uint8_t a_temp;
volatile uint8_t R_button;
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
	DDRA |= 0xFF;
	DDRB |= 0xFF;
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
	UCSR0B|=(1<<RXCIE0);
	sei(); 
}

uint8_t uart_receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}
ISR(USART0_RX_vect) {
		uartreg = uart_receive();
		A = uartreg;
//		_delay_ms(1000);
}
void play_pong(void) {
	if(B == 0b0000) {
		ball = 0;
	}
	else if(B == 0b0001) {
		ball = 1;
	}
	else if(B==0b0010) {
		ball = 2;
	}
	else if(B==0b0011) {
		ball= 3;
	}
	else if(B == 0b0100) {
		ball = 4;
	}
	else if(B==0b0101) {
		ball = 5;
	}
	else if(B==0b0110) {
		ball = 6;
	}
	else if (B == 0b0111) {
		ball = 7;
	}
	else if(B == 0b1000) {
		ball = 8;
	}
	else if (B == 0b1001) {
		ball = 9;
	}
	else if (B == 0b1010) {
		ball = 10;
	}
	
	
	



	// 		if(ball == 0) {
	// 			PORTA = 0b00011000;
	// 			_delay_ms(100);
	// 		}
	// 		else if (ball == 1) {
	// 			PORTA = 0b00110000;
	// 			_delay_ms(100);
	// 		}
	if (ball == 0) {
		PORTA= 0b00000000;
		_delay_ms(50);
	}
	else if (ball == 1) {
		PORTA= 0b00000001;
		_delay_ms(100);
	}
	else if (ball == 2) {
		PORTA= 0b00000010;
		_delay_ms(100);
	}
	else if (ball == 3) {
		PORTA = 0b00000011;
		_delay_ms(100);
	}
	else if (ball == 4) {
		PORTA = 0b00000100;
		_delay_ms(100);
	}
	else if (ball == 5) {
		PORTA = 0b00000101;
		_delay_ms(100);
	}
	else if (ball == 6) {
		PORTA = 0b00000110;
		_delay_ms(100);
	}
	else if (ball == 7) {
		PORTA = 0b00000111;
		_delay_ms(100);
	}
	else if (ball == 8) {
		PORTA = 0b00001000;
		_delay_ms(100);
	}
	else if (ball == 9) {
		PORTA = 0b00001001;
		_delay_ms(100);
	}
	else if (ball == 10) {
		PORTA = 0b00001010;
		_delay_ms(100);
	}
	// 		else if (ball == 11) {
	// 			PORTA = 0b00001011;
	// 			_delay_ms(100);
	// 		}
	
}
void play_stack(void) {
	PORTA= 0b00000000;
	_delay_ms(100);
	PORTA= 0b00000001;
	_delay_ms(100);
	PORTA= 0b00000010;
	_delay_ms(100);
	PORTA = 0b00000011;
	_delay_ms(100);
	PORTA = 0b00000100;
	_delay_ms(100);
	PORTA = 0b00000101;
	_delay_ms(100);
	PORTA = 0b00000110;
	_delay_ms(100);
	PORTA = 0b00000111;
	_delay_ms(100);
	PORTA = 0b00001000;
	_delay_ms(100);
	PORTA = 0b00001001;
	_delay_ms(100);
	PORTA = 0b00001010;
	_delay_ms(100);
}
int main(void)
{
    /* Replace with your application code */
	io_init();
	//i2c_init();
	uart_init();
	//gyro_init();
    while (1) 
    {
		//	PORTA = 0x00;
	//	value = ReadRegisterSingleByte(0x68, 0x75);
// 		i2c_start();
// 		i2c_write_address(0x68 << 1);
// 		i2c_write_address(0x19);
// 		i2c_write_data(0x07);
// 		i2c_stop();
// 		X = ReadRegisterSingleByte(0x68, 0x3C);
// 		XH_temp = ReadRegisterSingleByte(0x68, 0x3B);
// 		XH_temp = (XH_temp << 8);
// 		GyroX = XH_temp | X;
// 		
// 		Y = ReadRegisterSingleByte(0x68, 0x3E);
// 		YH_temp = ReadRegisterSingleByte(0x68, 0x3D);
// 		YH_temp = (YH_temp << 8);
// 		GyroY = YH_temp | Y;
// 
// 		Z = ReadRegisterSingleByte(0x68, 0x40);
// 		ZH_temp = ReadRegisterSingleByte(0x68, 0x3F);
// 		ZH_temp = (ZH_temp << 8);
// 		GyroZ = ZH_temp | Z;
// 		if (GyroY < -500) {
// 	//		PORTA = 0b00100000;
// 		}
// 		if (GyroY < -1000) {
// 			PORTA = 0b10000000;
// 		}
// 		if (GyroY > -80 && GyroY < 0) {
// 			PORTA = 0b00001000;
// 		}

// 		if (GyroY > 500) {
// 		PORTA = 0b00000100;
// 		}
// 		if (GyroY > 1000) {
// 			PORTA = 0b00000001;
// 		}
	//	PORTA = uartreg;
		

// // 		PORTB = 0xFF;
// // 		///_delay_ms(100);
// // 		PORTB = 0x00;
// // 		//_delay_ms(100);
		B = A;
		B_button = (B & 0b10000000);
		B_joystick = (B & 0b01110000);
// 		if(B_button == 0x80) {
// 			PORTA = 0b00001100;
// 		}
		while(B_button == 0 && pong_on == 0 && stack_on == 0) {
			B = A;
			B_button = (B & 0b10000000);
			B_joystick = (B & 0b01110000);
			if (B_joystick == 0x30) {
				a_temp = 0b00001101;
				PORTA = 0b00001101;
				//_delay_ms(100);
				//B = A;
			//	_delay_ms(10);
			//B_button = (B & 0b10000000);
			}
			if(B_joystick == 0x70)  {
				a_temp = 0b00001100;
				PORTA = 0b00001100;
				//_delay_ms(10);
			//	B_button = (B & 0b10000000);
			}
			B = A;
			B_button = (B & 0b11110000 );
			_delay_ms(100);
			if(B_button == 0x80 && a_temp == 0b00001100 ) {
				pong_on = 1;
				stack_on = 0;
			}
			if(B_button == 0x80 && a_temp == 0b00001101 ) {
				pong_on = 0;
				stack_on = 1;
			}
		
		}
		if(pong_on == 1) {
		play_pong();			
		}
		if(stack_on == 1) {
		play_stack();
		//stack_on = 0;
		}
			B = A;
			R_button = (A & 0b11110000 );
			_delay_ms(100);
			if(R_button == 0x80) {
				//B_joystick = 0;
				//a_temp = 0;
			//	B = 0;
				pong_on = 0;
				stack_on = 0;
			}


//		
// 		if(B_button == 0x80) {
// 			PORTB = 0x01;
// 		}
// 		else if(B_joystick == 0x70) {
// 			PORTB = 0x02;
// 		}
// 		else if (B_joystick == 0x30) {
// 			PORTB = 0x04;
// 		}
// 		else {
// 			PORTB = 0x00;
// 		}
	
	

		
    }
}

