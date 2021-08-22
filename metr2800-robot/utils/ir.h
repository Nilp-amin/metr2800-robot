/*
 * ir.h
 *
 * Created: 22/08/2021 3:14:05 PM
 *  Author: Nilp
 */ 


#ifndef IR_H_
#define IR_H_

#define F_CPU				16000000UL

#include <avr/interrupt.h>

#define READINGS			50
#define ADC0				0x00
#define ADC1				0x01
#define ADC2				0x02
#define ADC3				0x03
#define ADC4				0x04
#define ADC5				0x05
#define ADC6				0x06
#define ADC7				0x07


typedef struct {
	uint16_t ir1;
	uint16_t ir2;
	uint16_t ir3;
	uint16_t ir4;
	uint16_t ir5;
	uint16_t ir6;
	uint16_t ir7;
	uint16_t ir8;
} IrSensor;

void setupIR();
void readIRArray(IrSensor* sensors);


#endif /* IR_H_ */