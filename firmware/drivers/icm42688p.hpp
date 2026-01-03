#ifndef ICM42688P_H
#define ICM42688P_H

#include <Arduino.h>
#include <Wire.h>

class ICM42688P {
public:
	ICM42688P(uint8_t addr = 0x68);

	bool begin(TwoWire &wire = Wire);

	bool readAccel(int16_t &x, int16_t &y, int16_t &z);
	bool readGyro(int16_t &x, int16_t &y, int16_t &z);
	bool readTemp(int16_t &t);

private:
	uint8_t _addr;
	TwoWire *_wire;

	bool writeReg(uint8_t reg, uint8_t val);
	bool readRegs(uint8_t reg, uint8_t *buf, uint8_t len);
};

#endif

