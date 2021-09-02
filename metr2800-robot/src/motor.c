/*
 * motor.c
 *
 * Created: 20/08/2021 10:39:53 AM
 *  Author: Nilp
 */ 


#include "../utils/motor.h"

// Private scope functions
void writeStepper(uint8_t motor, uint8_t a, uint8_t b, uint8_t c, uint8_t d);
void onestep(uint8_t motor, uint8_t dir, uint8_t speed);
void var_delay(float delay); // delay in ms


void var_delay(float delay) {
	for (float i = 0; i < delay; i++) {
		_delay_ms(1);
	}
}

void setupDriveTrain() {
	// Set left stepper motor pins as outputs
	L_STEPPER_DDR |= (1 << L_STEPPER_PIN_1) | (1 << L_STEPPER_PIN_2) | (1 << L_STEPPER_PIN_3) | (1 << L_STEPPER_PIN_4);
					  
	// Set right stepper motor pins as outputs
	R_STEPPER_DDR |= (1 << R_STEPPER_PIN_1) | (1 << R_STEPPER_PIN_2) | (1 << R_STEPPER_PIN_3) | (1 << R_STEPPER_PIN_4);
	
	// Set turret stepper motor pins as outputs
	TURRET_DDR |= (1 << TURRET_PIN_1) | (1 << TURRET_PIN_2) | (1 << TURRET_PIN_3) | (1 << TURRET_PIN_4);
}

void writeStepper(uint8_t motor, uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
	if (motor == L_STEPPER) {
		L_STEPPER_PORT &= 0x0F;
		L_STEPPER_PORT |= (a << L_STEPPER_PIN_1) | (b << L_STEPPER_PIN_2) | (c << L_STEPPER_PIN_3) | (d << L_STEPPER_PIN_4);
	} else if (motor == R_STEPPER) {
		R_STEPPER_PORT &= 0xF0;
		R_STEPPER_PORT |= (a << R_STEPPER_PIN_1) | (b << R_STEPPER_PIN_2) | (c << R_STEPPER_PIN_3) | (d << R_STEPPER_PIN_4);
	} else if (motor == TURRET_STEPPER) {
		TURRET_PORT = (TURRET_PORT & 0xF0) | (a << TURRET_PIN_1) | (b << TURRET_PIN_2) | (c << TURRET_PIN_3) | (d << TURRET_PIN_4);
	}
}

void onestep(uint8_t motor, uint8_t dir, uint8_t speed) {
	if (dir == FORWARD) {
		writeStepper(motor, 1, 0, 0, 0);
		var_delay(speed);
		writeStepper(motor, 1, 1, 0, 0);
		var_delay(speed);
		writeStepper(motor, 0, 1, 0, 0);
		var_delay(speed);
		writeStepper(motor, 0, 1, 1, 0);
		var_delay(speed);
		writeStepper(motor, 0, 0, 1, 0);
		var_delay(speed);
		writeStepper(motor, 0, 0, 1, 1);
		var_delay(speed);
		writeStepper(motor, 0, 0, 0, 1);
		var_delay(speed);
		writeStepper(motor, 1, 0, 0, 1);
		var_delay(speed);
	} else if (dir == BACKWARD) {
		writeStepper(motor, 0, 0, 0, 1);
		var_delay(speed);
		writeStepper(motor, 0, 0, 1, 1);
		var_delay(speed);
		writeStepper(motor, 0, 0, 1, 0);
		var_delay(speed);
		writeStepper(motor, 0, 1, 1, 0);
		var_delay(speed);
		writeStepper(motor, 0, 1, 0, 0);
		var_delay(speed);
		writeStepper(motor, 1, 1, 0, 0);
		var_delay(speed);
		writeStepper(motor, 1, 0, 0, 0);
		var_delay(speed);
		writeStepper(motor, 1, 0, 0, 1);
		var_delay(speed);
	}
}

// Steps motors in parallel - faster
void parallelStep(uint8_t dir, uint8_t speed) {
	if (dir == FORWARD) {
		writeStepper(L_STEPPER, 1, 0, 0, 0);
		writeStepper(R_STEPPER, 1, 0, 0, 0);
		var_delay(speed);
		writeStepper(L_STEPPER, 1, 1, 0, 0);
		writeStepper(R_STEPPER, 1, 1, 0, 0);
		var_delay(speed);
		writeStepper(L_STEPPER, 0, 1, 0, 0);
		writeStepper(R_STEPPER, 0, 1, 0, 0);
		var_delay(speed);
		writeStepper(L_STEPPER, 0, 1, 1, 0);
		writeStepper(R_STEPPER, 0, 1, 1, 0);
		var_delay(speed);
		writeStepper(L_STEPPER, 0, 0, 1, 0);
		writeStepper(R_STEPPER, 0, 0, 1, 0);
		var_delay(speed);
		writeStepper(L_STEPPER, 0, 0, 1, 1);
		writeStepper(R_STEPPER, 0, 0, 1, 1);
		var_delay(speed);
		writeStepper(L_STEPPER, 0, 0, 0, 1);
		writeStepper(R_STEPPER, 0, 0, 0, 1);
		var_delay(speed);
		writeStepper(L_STEPPER, 1, 0, 0, 1);
		writeStepper(R_STEPPER, 1, 0, 0, 1);
	} else if (dir == BACKWARD) {
		writeStepper(L_STEPPER, 0, 0, 0, 1);
		writeStepper(R_STEPPER, 0, 0, 0, 1);
		var_delay(speed);
		writeStepper(L_STEPPER, 0, 0, 1, 1);
		writeStepper(R_STEPPER, 0, 0, 1, 1);
		var_delay(speed);
		writeStepper(L_STEPPER, 0, 0, 1, 0);
		writeStepper(R_STEPPER, 0, 0, 1, 0);
		var_delay(speed);
		writeStepper(L_STEPPER, 0, 1, 1, 0);
		writeStepper(R_STEPPER, 0, 1, 1, 0);
		var_delay(speed);
		writeStepper(L_STEPPER, 0, 1, 0, 0);
		writeStepper(R_STEPPER, 0, 1, 0, 0);
		var_delay(speed);
		writeStepper(L_STEPPER, 1, 1, 0, 0);
		writeStepper(R_STEPPER, 1, 1, 0, 0);
		var_delay(speed);
		writeStepper(L_STEPPER, 1, 0, 0, 0);
		writeStepper(R_STEPPER, 1, 0, 0, 0);
		var_delay(speed);
		writeStepper(L_STEPPER, 1, 0, 0, 1);
		writeStepper(R_STEPPER, 1, 0, 0, 1);
	}
}

void powerDownDriveTrain() {
	writeStepper(L_STEPPER, 0, 0, 0, 0);
	writeStepper(R_STEPPER, 0, 0, 0, 0);
	writeStepper(TURRET_STEPPER, 0, 0, 0, 0);
}


void forwardStep(uint16_t dist, uint8_t speed) {
	powerDownDriveTrain(); // Lets steppers break down mag field
	_delay_ms(200);
	for (uint16_t i = 0; i < dist; i++) {
		onestep(R_STEPPER, FORWARD, speed);
		onestep(L_STEPPER, FORWARD, speed);
	}
}



void backwardStep(uint16_t dist, uint8_t speed) {
	powerDownDriveTrain(); // Lets steppers break down mag field
	_delay_ms(200);
	for (uint16_t i = 0; i < dist; i++) {
		onestep(L_STEPPER, BACKWARD, speed);
		onestep(R_STEPPER, BACKWARD, speed);
	}
}


// Only coded for turret right now
void rotateCW(uint16_t angle, uint8_t speed) {
	powerDownDriveTrain(); // Lets steppers break down mag field
	_delay_ms(200);
	for (int i = 0; i < angle; i++) {
		onestep(L_STEPPER, FORWARD, speed);
		onestep(R_STEPPER, BACKWARD, speed);
	}
}

// Only coded for turret right now
void rotateCCW(uint16_t angle, uint8_t speed) {
	powerDownDriveTrain(); // Lets steppers break down mag field
	_delay_ms(200);
	for (int i = 0; i < angle; i++) {
		onestep(L_STEPPER, BACKWARD, speed);
		onestep(R_STEPPER, FORWARD, speed);
	}
}