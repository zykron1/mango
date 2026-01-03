#include "pid.hpp"

PID::PID(float kp, float ki, float kd)
	: _kp(kp), _ki(ki), _kd(kd),
	  _setpoint(0.0f),
	  _integral(0.0f),
	  _prevError(0.0f),
	  _outMin(-1e9f),
	  _outMax(1e9f) {}

void PID::setGains(float kp, float ki, float kd) {
	_kp = kp;
	_ki = ki;
	_kd = kd;
}

void PID::setOutputLimits(float minOut, float maxOut) {
	_outMin = minOut;
	_outMax = maxOut;
}

void PID::setSetpoint(float setpoint) {
	_setpoint = setpoint;
}

float PID::update(float measurement, float dt) {
	float error = _setpoint - measurement;
	_integral += error * dt;
	float derivative = (error - _prevError) / dt;
	_prevError = error;

	float out = _kp * error + _ki * _integral + _kd * derivative;

	if (out > _outMax) out = _outMax;
	if (out < _outMin) out = _outMin;

	return out;
}

void PID::reset() {
	_integral = 0.0f;
	_prevError = 0.0f;
}

