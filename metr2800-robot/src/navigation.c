#include "../utils/navigation.h"

// notes TODO :: work out if ints should be int16_t
// Check pins against schematic, then add second ultrasonic sensor

void setupNavSensors() {
	DDRD = (1 << PORTD0); //0b00000011;
	//PORTD = 0b00000000;
	
	EIMSK |= (1<<INT0);
	EICRA |= (1<<ISC00);
	
	TCCR1B = (0<<CS12)|(1<<CS11)|(1<<CS10);
	sei();
	return;
}

int readDistance(int sensor) {
	// select which sensor to read with 0 or 1, call readDistance twice in succession. 
	hc_sr04_cnt = 0;
	if (sensor == 0) {
		PORTD |= (1<<PORTD0);
		_delay_us(12);
		PORTD &= ~(1<<PORTD0);
	} else if (sensor == 1) {
		PORTD |= (1<<1);
		_delay_us(12);
		PORTD &= ~(1<<1);
	}

	while (hc_sr04_cnt == 0); // loops until gets value

	return 0.000004 * hc_sr04_cnt/2 * 34300;
}

/*Measures time from trigger to echo of either of the ultrasonic sensors. */
ISR(INT0_vect) {
	if (PIND & (1<<PIND3) || PIND & (1<<PIND3)) {
		TCNT1 = 0;
	} else {
		hc_sr04_cnt = TCNT1;
	}
}

float distanceCentre(int x, int y) {
	float value = sqrt(pow((50-x),2) + pow((50-y),2));
	return value;
}

float angleCentre(int x, int y) {
	float angle = atan((50-y)/(50-x));
	return angle;
}

void locate() {
	int dist[50]; // calibrate array size, will be based on move angle 
	int dist2[50];
	int moveAngle = 5;
	for (int i=0; i<50; i++) {
		move(moveAngle, 0); // replace with move method, add import to header, may be in motor file
		dist[i] = readDistance(0);
		dist2[i] = readDistance(1);
	}
	
	int angleToSquare;
	int currentCoord[2];
	for (int i=0; i<50; i++) {
		if (dist[i] + dist2[i] > 25  && dist[i] + dist2[i] < 35) { 
			if (dist[i+90/moveAngle] + dist2[i+90/moveAngle] > 98 && dist2[i+90/moveAngle] + dist2[i+90/moveAngle] < 101) {
				angleToSquare = i * moveAngle;
				currentCoord[0] = (dist[i] < dist2[i]) ? dist[i] : dist2[i];
				currentCoord[1] = (dist[i+90/moveAngle] < dist2[i+90/moveAngle]) ? dist[i+90/moveAngle] : dist2[i+90/moveAngle];
				break;
			}
		}
	}
	float distCentre = distanceCentre(currentCoord[0], currentCoord[1]);
	float angle = angleCentre(currentCoord[0], currentCoord[1]);
	// might be best to have these values stored in a struct, and return the struct. 
	return;
}


