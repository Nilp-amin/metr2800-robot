/*
 * motor.c
 *
 * Created: 20/08/2021 10:39:53 AM
 *  Author: Nilp
 */ 


#include "../utils/motor.h"

// Private scope functions
void writeStepper(uint8_t motor, uint8_t a, uint8_t b, uint8_t c, uint8_t d);
void onestep(uint8_t motor, uint8_t dir);


void setupDriveTrain() {
	// Set left stepper motor pins as outputs
	L_STEPPER_DDR |= (1 << L_STEPPER_PIN_1) | (1 << L_STEPPER_PIN_2) | (1 << L_STEPPER_PIN_3) | (1 << L_STEPPER_PIN_4);
					  
	// Set right stepper motor pins as outputs
	R_STEPPER_DDR |= (1 << R_STEPPER_PIN_1) | (1 << R_STEPPER_PIN_2) | (1 << R_STEPPER_PIN_3) | (1 << R_STEPPER_PIN_4);
}

void writeStepper(uint8_t motor, uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
	if (motor == L_STEPPER) {
		L_STEPPER_PORT = (L_STEPPER_PORT & 0x0F) | (a << L_STEPPER_PIN_1) | (b << L_STEPPER_PIN_2) | (c << L_STEPPER_PIN_3) | (d << L_STEPPER_PIN_4);
	} else if (motor == R_STEPPER) {
		R_STEPPER_PORT = (R_STEPPER_PORT & 0xF0) | (a << R_STEPPER_PIN_1) | (b << R_STEPPER_PIN_2) | (c << R_STEPPER_PIN_3) | (d << R_STEPPER_PIN_4);
	}
}

void onestep(uint8_t motor, uint8_t dir) {
	if (dir == FORWARD) {
		writeStepper(motor, 1, 0, 0, 0);
		_delay_ms(STEPPER_SPEED);
		writeStepper(motor, 1, 1, 0, 0);
		_delay_ms(STEPPER_SPEED);
		writeStepper(motor, 0, 1, 0, 0);
		_delay_ms(STEPPER_SPEED);
		writeStepper(motor, 0, 1, 1, 0);
		_delay_ms(STEPPER_SPEED);
		writeStepper(motor, 0, 0, 1, 0);
		_delay_ms(STEPPER_SPEED);
		writeStepper(motor, 0, 0, 1, 1);
		_delay_ms(STEPPER_SPEED);
		writeStepper(motor, 0, 0, 0, 1);
		_delay_ms(STEPPER_SPEED);
		writeStepper(motor, 1, 0, 0, 1);
	} else if (dir == BACKWARD) {
		writeStepper(motor, 0, 0, 0, 1);
		_delay_ms(STEPPER_SPEED);
		writeStepper(motor, 0, 0, 1, 1);
		_delay_ms(STEPPER_SPEED);
		writeStepper(motor, 0, 0, 1, 0);
		_delay_ms(STEPPER_SPEED);
		writeStepper(motor, 0, 1, 1, 0);
		_delay_ms(STEPPER_SPEED);
		writeStepper(motor, 0, 1, 0, 0);
		_delay_ms(STEPPER_SPEED);
		writeStepper(motor, 1, 1, 0, 0);
		_delay_ms(STEPPER_SPEED);
		writeStepper(motor, 1, 0, 0, 0);
		_delay_ms(STEPPER_SPEED);
		writeStepper(motor, 1, 0, 0, 1);
	}
}

void powerDownDriveTrain() {
	writeStepper(L_STEPPER, 0, 0, 0, 0);
	writeStepper(R_STEPPER, 0, 0, 0, 0);
}

void rotateCW(uint16_t angle) {
	for (int i = 0; i < angle; i++) {
		onestep(L_STEPPER, FORWARD);
		onestep(R_STEPPER, BACKWARD);
	}
}

void rotateCCW(uint16_t angle) {
	for (int i = 0; i < angle; i++) {
		onestep(L_STEPPER, BACKWARD);
		onestep(R_STEPPER, FORWARD);
	}
}