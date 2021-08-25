/*
 * motor.h
 *
 * Created: 15/08/2021 11:57:03 PM
 *  Author: Nilp
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#define F_CPU	16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BACKWARD				0
#define FORWARD					1
#define STEPPER_SPEED			2 // Lowest we can get it before slip occurs

// Left stepper motor
#define L_STEPPER				0
#define L_STEPPER_DDR			DDRC
#define L_STEPPER_PORT			PORTC
#define L_STEPPER_PIN_1			PORTC7
#define	L_STEPPER_PIN_2			PORTC6
#define L_STEPPER_PIN_3			PORTC5
#define L_STEPPER_PIN_4			PORTC4

// Right stepper motor
#define R_STEPPER				1
#define R_STEPPER_DDR			DDRC
#define R_STEPPER_PORT			PORTC
#define R_STEPPER_PIN_1			PORTC3
#define R_STEPPER_PIN_2			PORTC2
#define R_STEPPER_PIN_3			PORTC1
#define R_STEPPER_PIN_4			PORTC0

void setupDriveTrain();
void powerDownDriveTrain();

// Steps are codded to be 512 per 360 deg.
// TODO :: do some maths to figure out steps required to achieve given angle --> currently coded so that 1 angle == 1 step
void rotateCW(uint16_t angle);
void rotateCCW(uint16_t angle);

#endif /* MOTOR_H_ */