#include "icm42688p.h"

#define REG_WHO_AM_I     0x75
#define REG_PWR_MGMT0   0x4E
#define REG_ACCEL_DATA  0x1F
#define REG_GYRO_DATA   0x25
#define REG_TEMP_DATA   0x1D

#define WHO_AM_I_VAL    0x47

ICM42688P::ICM42688P(uint8_t addr)
	: _addr(addr), _wire(nullptr) {}

bool ICM42688P::begin(TwoWire &wire) {
	_wire = &wire;
	_wire->begin();

	uint8_t id = 0;
	if (!readRegs(REG_WHO_AM_I, &id, 1)) return false;
	if (id != WHO_AM_I_VAL) return false;

	if (!writeReg(REG_PWR_MGMT0, 0x0F)) return false;

	return true;
}

bool ICM42688P::readAccel(int16_t &x, int16_t &y, int16_t &z) {
	uint8_t b[6];
	if (!readRegs(REG_ACCEL_DATA, b, 6)) return false;
	x = (int16_t)((b[0] << 8) | b[1]);
	y = (int16_t)((b[2] << 8) | b[3]);
	z = (int16_t)((b[4] << 8) | b[5]);
	return true;
}

bool ICM42688P::readGyro(int16_t &x, int16_t &y, int16_t &z) {
	uint8_t b[6];
	if (!readRegs(REG_GYRO_DATA, b, 6)) return false;
	x = (int16_t)((b[0] << 8) | b[1]);
	y = (int16_t)((b[2] << 8) | b[3]);
	z = (int16_t)((b[4] << 8) | b[5]);
	return true;
}

bool ICM42688P::readTemp(int16_t &t) {
	uint8_t b[2];
	if (!readRegs(REG_TEMP_DATA, b, 2)) return false;
	t = (int16_t)((b[0] << 8) | b[1]);
	return true;
}

bool ICM42688P::writeReg(uint8_t reg, uint8_t val) {
	_wire->beginTransmission(_addr);
	_wire->write(reg);
	_wire->write(val);
	return _wire->endTransmission() == 0;
}

bool ICM42688P::readRegs(uint8_t reg, uint8_t *buf, uint8_t len) {
	_wire->beginTransmission(_addr);
	_wire->write(reg);
	if (_wire->endTransmission(false) != 0) return false;

	uint8_t n = _wire->requestFrom(_addr, len);
	if (n != len) return false;

	for (uint8_t i = 0; i < len; i++) {
		buf[i] = _wire->read();
	}
	return true;
}

