/*
 * metr2800-robot.c
 *
 * Created: 15/08/2021 11:00:45 PM
 * Author : Nilp
 */ 

#define F_CPU	16000000UL

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "utils/motor.h"
#include "utils/uart.h"


int main(void)
{
    /* Replace with your application code */
    while (1) {
		break;
    }
	
	rotateCW(20);
	rotateCCW(30);
}

