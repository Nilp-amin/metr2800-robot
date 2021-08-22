/*
 * ir.c
 *
 * Created: 22/08/2021 3:14:33 PM
 *  Author: Nilp
 */ 

#include "../utils/ir.h"

// private scope
uint16_t readADC(uint8_t adcNum);

void setupIR() {
	// Set AVCC as ref voltage
	ADMUX |= (1 << REFS0);
	// Turn on ADC with free running mode and set clk to 125 KHz
	ADCSRA |= (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	// Convert all ADC0-7 pins to analog
	DIDR0 |= 0xFF;
}

uint16_t readADC(uint8_t adcNum) {
	// Select the correct adc pin
	ADMUX = (ADMUX & 0xF0) | adcNum;
	int sum = 0;
	for (int i = 0; i < READINGS+2; i++) {
		if (i < 2) {
			// Throw away the first two readings
			uint16_t throwAway = ADCL | (ADCH << 8);
		}
		sum += ADCL | (ADCH << 8);
	}
	return sum / READINGS;
}

void readIRArray(IrSensor* sensors) {
	sensors->ir1 = readADC(ADC0);
	sensors->ir2 = readADC(ADC1);
	sensors->ir3 = readADC(ADC2);
	sensors->ir4 = readADC(ADC3);
	sensors->ir5 = readADC(ADC4);
	sensors->ir6 = readADC(ADC5);
	sensors->ir7 = readADC(ADC6);
	sensors->ir8 = readADC(ADC7);
}