#ifndef SG90_SERVO_H
#define SG90_SERVO_H

#include <Arduino.h>

class SG90Servo {
public:
	SG90Servo(uint8_t pin);
	void begin();
	void write(uint8_t angle);
	void writeMicroseconds(uint16_t us);
	void update();

private:
	uint8_t _pin;
	uint16_t _pulse;
	unsigned long _last;
};

#endif

