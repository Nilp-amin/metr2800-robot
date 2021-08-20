/*
 * motor.h
 *
 * Created: 15/08/2021 11:57:03 PM
 *  Author: Nilp
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void moveCW(uint16_t angle);
void moveCCW(uint16_t angle);

#endif /* MOTOR_H_ */