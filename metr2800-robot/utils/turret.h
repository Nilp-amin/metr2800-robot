/*
 * turret.h
 *
 * Created: 22/08/2021 3:14:49 PM
 *  Author: Nilpa
 */ 


#ifndef TURRET_H_
#define TURRET_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define LASER_DDR				DDRD
#define LASER_PORT				PORTD
#define LASER_PIN				PORTD6

void setupLaser(void);
void shootLaser(void);


#endif /* TURRET_H_ */