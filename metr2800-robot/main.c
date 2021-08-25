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
#include "utils/navigation.h"
#include "utils/uart.h"
#include "utils/ir.h"
#include "utils/turret.h"

int main(void) {

	
    setupDriveTrain();
	setupLaser();
	setupNavSensors();
	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
	DDRD |= (1 << DDRD7);
	sei();
	uart_puts("Hello World\n");
    while (1) {
		/*
		_delay_ms(1000);

		PORTD ^= (1 << PORTD7);
		shootLaser();
		_delay_ms(1000);
		*/
    }
}


