#include "../utils/navigation.h"/

// notes TODO :: work out if ints should be int16_t
// Check pins against schematic, then add second ultrasonic sensor

void setupNavSensors() {	
<<<<<<< HEAD
	DDRD = 0b11111011; // set one input device, need to set another when know correct pins
	_delay_ms(50);
	
	GICR |= 1<<INT0 // why red?
	MCUCR |= 1<<ISC00;

	sei();
=======
	DDRB = (1<<MOSI)|(1<<SSK)|(1<<SS)|(1<<RST)|(1<<DC);
	
	DDRD = 0b00001000;
	PORTD = 0b00000000;
>>>>>>> d41dae839f525e9dc2978ba4c9aed7dd6e8df814
	
	EIMSK |= (1<<INT0);
	EICRA |= (1<<ISC00);
	
	TCCR1B = (0<<CS12)|(1<<CS11)|(1<<CS10);
	return;
}

int readDistance(int sensor) {	
	// reads from one ultrasonic sensor, will make it read from different sensors based on input
<<<<<<< HEAD
	PORTD |= 1<<PIND0;
	_delay_us(15);

	PORTD &= ~(1<<PIND0);
	int16_t distance = pulse/58;
	return distance;
=======
	hc_sr04_cnt = 0;
	
	PORTD |= (1<<3);
	_delay_us(10);
	PORTD &= ~(1<<3);
	
	while (hc_sr04_cnt = 0); // loops until gets value
	
	return 0.000004 * hc_sr04_cnt/2 * 34300;
>>>>>>> d41dae839f525e9dc2978ba4c9aed7dd6e8df814
}

ISR(INT0_vect) {
	// this could be better implemented in another file
	// set the pulse width when delay sent
	
	if (PIND & (1<<2)) {
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
	int dist[50];
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
}


