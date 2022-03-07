#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

struct motor {
  byte forward;
  byte backward;
};

//struct motor;

void StopMotor(motor *m);
void SetMotor(motor *m, bool forward);
void ManageMotors(motor *screw, motor *platform);

void StayScrewPos(motor *screw, byte pos);
void StayPlatformPos(motor *platform, byte pos);

#endif
