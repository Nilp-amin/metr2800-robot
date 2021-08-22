#ifndef NAVIGATION_H_
#define NAVIGATION_H_

#define F_CPU	16000000UL

#include <stdio.h>
#include <avr/io.h>
#include <math.h>
#include <util/delay.h>

#define  Trigger_pin	PA0 // confirm with schematic
static volatile int pulse = 0;
static volatile int i = 0;

void setupNavSensors();
int readDistance(int sensor);
ISR(INT0_vect); // may already be implemented in another file
float distanceCentre(int x, int y);
float angleCentre(int x, int y);
void locate();

#endif /*NAVIGATION_H_ */