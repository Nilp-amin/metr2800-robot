/*
 * turret.c
 *
 * Created: 22/08/2021 3:14:58 PM
 *  Author: Nilp
 */ 

#include "../utils/turret.h"

void setupLaser() {
	LASER_DDR |= (1 << LASER_PIN);
}

void shootLaser() {
	LASER_PORT |= (1 << LASER_PIN);
	_delay_ms(2000);
	LASER_PORT &= ~(1 << LASER_PIN);
}
