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


int main(void) {

	
    setupDriveTrain();
	DDRD = (1 << DDRD7);
    while (1) {
		PORTD ^= (1 << PORTD7);
		rotateCW(512);
		powerDownDriveTrain();
		_delay_ms(1000);
		rotateCCW(512);
    }

	
	
	rotateCW(20);
	rotateCCW(30);
}

