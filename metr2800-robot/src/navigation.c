#include "../utils/navigation.h"/

// notes TODO :: work out if ints should be int16_t
// Check pins against schematic, then add second ultrasonic sensor

void setupNavSensors() {	
	DDRD = 0b11111011; // set one input device, need to set another when know correct pins
	_delay_ms(50);

	GICR |= 1<<INT0 // why red?
	MCUCR |= 1<<ISC00;

	sei();
	
	return;
}

int readDistance(int sensor) {	
	// reads from one ultrasonic sensor, will make it read from different sensors based on input
	PORTD |= 1<<PIND0;
	_delay_us(15);

	PORTD &= ~(1<<PIND0);
	int16_t distance = pulse/58;
	return distance
}

ISR(INT0_vect) {
	// this could be better implemented in another file
	// set the pulse width when delay sent
	if (i == 0) {
		TCCR1B |= 1<<CS10;
		i = 1;
	}
	else { 
		TCCR1B = 0;
		pulse = TCNT1;
		TCNT1 = 0;
		i = 0;
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
	int dist[50];
	int dist2[50];
	int moveAngle = 5;
	for (int i=0; i<50l i++) {
		move(moveAngle, 0); // replace with move method, add import to header, may be in motor file
		dist[i] = readDistance();
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
}


