/*
 * uart.c
 *
 * Created: 20/08/2021 10:46:57 AM
 *  Author: Nilp
 */ 

#include "../utils/uart.h"


volatile uint8_t serialReadPos = 0;
volatile uint8_t serialWritePos = 0;

void setupUART() {
	UBRR0H = (BRC >> 8);
	UBRR0L = BRC;
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << TXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	
	sei();
}

void appendSerial(char c) {
	serialBuffer[serialWritePos] = c;
	serialWritePos++;
	
	if (serialWritePos >= TX_BUFFER_SIZE) {
		serialWritePos = 0;
	}
}

void serialWrite(char c[]) {
	for (uint8_t i = 0; i < strlen(c); i++) {
		appendSerial(c[i]);
	}
	
	if (UCSR0A & (1 << UDRE0)) {
		UDR0 = 'c';
	}
}

ISR(USART0_TX_vect) {
	if (serialReadPos != serialWritePos) {
		UDR0 = serialBuffer[serialReadPos];
		serialReadPos++;
		
		if (serialReadPos >= TX_BUFFER_SIZE) {
			serialReadPos = 0; // I changed this --> test
		}
	}
	PORTD ^= (1 << PORTD7);
}
