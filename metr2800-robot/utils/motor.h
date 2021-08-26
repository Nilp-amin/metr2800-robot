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
#define STEP_ANGLE				(360/512)
#define WHEEL_RADIUS			30 // In mm

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

// Turret stepper motor
#define TURRET_STEPPER			2
#define TURRET_DDR				DDRB
#define TURRET_PORT				PORTB
#define TURRET_PIN_1			PORTB3
#define TURRET_PIN_2			PORTB2
#define TURRET_PIN_3			PORTB1
#define TURRET_PIN_4			PORTB0

void setupDriveTrain();
void powerDownDriveTrain();

void parallelStep(uint8_t dir, uint8_t speed);
void forwardStep(uint16_t dist, uint8_t speed);
void backwardStep(uint16_t dist, uint8_t speed);

// Steps are codded to be 512 per 360 deg.
// TODO :: do some maths to figure out steps required to achieve given angle --> currently coded so that 1 angle == 1 step
void rotateCW(uint16_t angle, uint8_t speed);
void rotateCCW(uint16_t angle, uint8_t speed);

#endif /* MOTOR_H_ */