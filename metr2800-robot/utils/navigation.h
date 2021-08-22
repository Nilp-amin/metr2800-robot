#ifndef NAVIGATION_H_
#define NAVIGATION_H_

#define F_CPU	16000000UL

#include <stdio.h>
#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// added section start
#define MOSI 3 // PORT B, pin 3
#define MISO 4 // Port B, Pin 4
#define SSK 5
#define SS 2

#define RST 0

#define DC 1

volatile unsigned short hc_sr04_cnt;
// added end
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