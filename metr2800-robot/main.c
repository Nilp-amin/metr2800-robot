/*
 * metr2800-robot.c
 *
 * Created: 15/08/2021 11:00:45 PM
 * Author : Nilp
 */ 

#define F_CPU	16000000UL

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "utils/motor.h"
#include "utils/uart.h"


int main(void)
{
    /* Replace with your application code */
	DDRD = (1 << DDRD7);
    while (1) {
		PORTD ^= (1 << PORTD7);
		_delay_ms(50);
    }

	
	
	moveCW(20);
	moveCCW(30);
}

