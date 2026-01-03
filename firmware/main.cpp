#include <Arduino.h>
#include "drivers/icm42688p.h"
#include "drivers/SG90Servo.h"
#include "pid.h"

#define MOTOR_FL 3
#define MOTOR_FR 5
#define MOTOR_BL 6
#define MOTOR_BR 9

ICM42688P imu;

SG90Servo mFL(MOTOR_FL);
SG90Servo mFR(MOTOR_FR);
SG90Servo mBL(MOTOR_BL);
SG90Servo mBR(MOTOR_BR);

PID pidRoll(1.2f, 0.0f, 0.04f);
PID pidPitch(1.2f, 0.0f, 0.04f);
PID pidYaw(1.0f, 0.0f, 0.02f);

float roll = 0.0f;
float pitch = 0.0f;
float yaw = 0.0f;

unsigned long lastMicros = 0;

void setup() {
	imu.begin();

	mFL.begin();
	mFR.begin();
	mBL.begin();
	mBR.begin();

	pidRoll.setSetpoint(0.0f);
	pidPitch.setSetpoint(0.0f);
	pidYaw.setSetpoint(0.0f);

	pidRoll.setOutputLimits(-30, 30);
	pidPitch.setOutputLimits(-30, 30);
	pidYaw.setOutputLimits(-20, 20);

	lastMicros = micros();
}

void loop() {
	mFL.update();
	mFR.update();
	mBL.update();
	mBR.update();

	unsigned long now = micros();
	float dt = (now - lastMicros) * 1e-6f;
	lastMicros = now;

	int16_t gx, gy, gz;
	if (!imu.readGyro(gx, gy, gz)) return;

	float gyroX = gx * 0.000266f;
	float gyroY = gy * 0.000266f;
	float gyroZ = gz * 0.000266f;

	roll  += gyroX * dt;
	pitch += gyroY * dt;
	yaw   += gyroZ * dt;

	float rollOut  = pidRoll.update(roll, dt);
	float pitchOut = pidPitch.update(pitch, dt);
	float yawOut   = pidYaw.update(yaw, dt);

	int base = 90;

	mFL.write(base + pitchOut + rollOut - yawOut);
	mFR.write(base + pitchOut - rollOut + yawOut);
	mBL.write(base - pitchOut + rollOut + yawOut);
	mBR.write(base - pitchOut - rollOut - yawOut);
}

