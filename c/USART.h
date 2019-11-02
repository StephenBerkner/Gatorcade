/*
USART.h
*/

#ifndef USART_STRING_COM_H_
#define USART_STRING_COM_H_


#include <avr/io.h>
#include <avr/interrupt.h>

// INITIALIZATIONS/
#define F_CPU 1000000       // ATmega324p runs at 1MHz
#define BSCALE115200	-7
#define BSEL115200	11
#define NULL 0x00

#define BAUD 9600
#define UBRRVAL ((F_CPU / (16UL * BAUD)) - 1)

uint8_t USARTDataReceived = 0x00;





void USARTInit(void) {
	UCSR0C |= (0 << UMSEL00) | (0 << UMSEL01);
	UBRR0H = (unsigned int)(UBRRVAL>>8);
	UBRR0L = (unsigned int) UBRRVAL;
	DDRD |= 0x03;//0b00000110;
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	UCSR0C |= (1 <<UCSZ00) | (1 << UCSZ01);
	UCSR0B|=(1<<RXCIE0);
	sei();
}

uint8_t USARTReceive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}


uint8_t USARTTransmit(uint8_t data) {
	while((UCSR0A & (1<<UDRE0)) == 0);

	// Transmit data
	UDR0 = data;
}

//receive ISR
ISR(USART0_RX_vect) {
	USARTDataReceived = USARTReceive();
	//		_delay_ms(1000);
}


#endif
