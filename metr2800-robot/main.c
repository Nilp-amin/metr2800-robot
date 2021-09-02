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

void navCode() {
	setupNavSensors();
	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
	while (1) {
		int dist = readDistance(0);
		char buff[128];
		sprintf(buff, "%i\n\r", dist);
		uart_puts("Distance measured:\n\r");
		uart_puts(buff);
		_delay_ms(500);
	}
}

void intellCode() {
	setupNavSensors();
	setupDriveTrain();
	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
	while (1) {
		int dist = readDistance(0);
		forwardStep(1, 1);
		if (dist < 10) {
			powerDownDriveTrain();
			_delay_ms(1000);
			backwardStep(512, 1);
		}
	}
}


void driveTrainCode() {
	setupDriveTrain();
	while (1) {
		forwardStep(512, 1);
		backwardStep(512, 1);
		powerDownDriveTrain();
		_delay_ms(1000);
	}
}

void turretCode() {
	setupDriveTrain();
	while (1) {
		rotateCW(512, 1);
		rotateCCW(512, 1);
		powerDownDriveTrain();
		_delay_ms(1000);
	}
}

void IRCode() {
	setupLaser();
	setupIR();
	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
	IrSensor sensors;
	uart_puts("Starting IR:\n\r");
	while (1) {
		readIRArray(&sensors);
		char buff[128];
		sprintf(buff, "%i\n\r", sensors.ir8);
		uart_puts("IR light readings:\n\r");
		uart_puts(buff);
		_delay_ms(100);
		if (sensors.ir8 > 200) {
			shootLaser();
		}
	}
}

int main(void) {
	sei();
	_delay_ms(100);
	driveTrainCode();
}


