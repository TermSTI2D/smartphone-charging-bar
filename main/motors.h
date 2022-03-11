#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

/* Motor pins ( Enable - In1 - In2 ) */
#define ScrewMotorEnable 0
#define ScrewMotorUp 4
#define ScrewMotorDown 5

#define PlatformMotorEnable 0
#define PlatformMotorAntiClockwise 6
#define PlatformMotorClockwise 7

#define SETSTATES 0  // Set to one if "Enable" pins are set to other pins than 0

/* Limit switch pins */
#define LSUp 2
#define LSDown 2
#define LSPlatform 3


struct motor {
  byte forward;
  byte backward;
};

void InitMotors(motor & screw, motor & platform);
void SetMotorStates(bool state);
void ManageMotors(motor *screw, motor *platform);

void StopMotor(motor *m);
void SetMotor(motor *m, bool forward);

void StayScrewPos(motor *screw, byte pos);
void StayPlatformPos(motor *platform, byte pos);

#endif
