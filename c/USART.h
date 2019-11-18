/*
USART.h
*/

#ifndef USART_STRING_COM_H_
#define USART_STRING_COM_H_


#include <avr/io.h>
#include <avr/interrupt.h>

// INITIALIZATIONS/
//#define F_CPU 1000000       // ATmega324p runs at 1MHz
//#define BSCALE115200	-7
//#define BSEL115200	11
//#define NULL 0x00

#define BAUD 2400
#define UBRRVAL ((F_CPU / (16UL * BAUD)) - 1)

//volatile uint8_t USARTDataReceived = 0x00;

volatile uint8_t PlayerOneUSARTData = 0x00;
volatile uint8_t PlayerTwoUSARTData = 0x00;


//initializes USART0 and USART 1
void USARTInit(void) {
	UCSR0C |= (0 << UMSEL00) | (0 << UMSEL01);
	UBRR0H = (unsigned int)(UBRRVAL>>8);
	UBRR0L = (unsigned int) UBRRVAL;
	//DDRD |= 0x03;//0b00000110;
	//DDRD &= ~(0x05); //RX1 and RX2 as input
	
	DDRD &= ~0x05;
	//DDRD |= 0x02;
	
	//RX0
	UCSR0B |= (1<<RXEN0) | (1 << TXEN0);//enable receive uncomment this to enable transmit|(1<<TXEN0);
	UCSR0B|=(1<<RXCIE0);
	
	
	UCSR0C |= (1 <<UCSZ00) | (1 << UCSZ01);
	
	UCSR1C |= (0 << UMSEL10) | (0 << UMSEL11);
	UBRR1H = (unsigned int)(UBRRVAL>>8);
	UBRR1L = (unsigned int) UBRRVAL;
	
	UCSR1B |= (1<<RXEN1);
	UCSR1B |= (1<<RXCIE1);
	
	UCSR1C |= (1 << UCSZ10) | (1 << UCSZ11);
	
	sei();
}

//USART0 functions
uint8_t USART0Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}


void USART0Transmit(uint8_t data) {
	while((UCSR0A & (1<<UDRE0)) == 0);

	// Transmit data
	UDR0 = data;
	
	//return 0x00;
}

//receive ISR
ISR(USART0_RX_vect) {
	PlayerOneUSARTData = USART0Receive();
	
	//_delay_us(1);
	//uncomment to echo
	//USART0Transmit(USARTDataReceived);
}


//USART1 functions
uint8_t USART1Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR1A & (1<<RXC1)) );
	/* Get and return received data from buffer */
	return UDR1;
}


void USART1Transmit(uint8_t data) {
	while((UCSR1A & (1<<UDRE1)) == 0);

	// Transmit data
	UDR1 = data;
	
	//return 0x00;
}

//receive ISR
ISR(USART1_RX_vect) {
	PlayerTwoUSARTData = USART1Receive();
	
	//uncomment to echo
	//USART1Transmit(USARTDataReceived);
}





#endif
