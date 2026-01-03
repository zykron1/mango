#include "SG90Servo.h"

/* 
 Can be refactored to use for ESC's
 * */

SG90Servo::SG90Servo(uint8_t pin)
	: _pin(pin), _pulse(1500), _last(0) {}

void SG90Servo::begin() {
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
}

void SG90Servo::write(uint8_t angle) {
	angle = constrain(angle, 0, 180);
	_pulse = map(angle, 0, 180, 500, 2400);
}

void SG90Servo::writeMicroseconds(uint16_t us) {
	_pulse = constrain(us, 500, 2400);
}

void SG90Servo::update() {
	unsigned long now = micros();
	if (now - _last >= 20000) {
		_last = now;
		digitalWrite(_pin, HIGH);
		delayMicroseconds(_pulse);
		digitalWrite(_pin, LOW);
	}
}

