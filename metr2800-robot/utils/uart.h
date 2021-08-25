/*
 * uart.h
 *
 * Created: 20/08/2021 10:46:45 AM
 *  Author: Nilp
 */ 


#ifndef UART_H_
#define UART_H_

#define F_CPU				16000000UL
#define BAUD				9600
#define BRC					((F_CPU/16/BAUD) - 1)
#define TX_BUFFER_SIZE		128

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

char serialBuffer[TX_BUFFER_SIZE];

void setupUART(void);
void appendSerial(char c);

#endif /* UART_H_ */