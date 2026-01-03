#ifndef PID_H
#define PID_H

class PID {
public:
	PID(float kp, float ki, float kd);

	void setGains(float kp, float ki, float kd);
	void setOutputLimits(float minOut, float maxOut);
	void setSetpoint(float setpoint);

	float update(float measurement, float dt);
	void reset();

private:
	float _kp;
	float _ki;
	float _kd;

	float _setpoint;
	float _integral;
	float _prevError;

	float _outMin;
	float _outMax;
};

#endif

