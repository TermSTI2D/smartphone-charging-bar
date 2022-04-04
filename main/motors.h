#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include "pins.h"
#include "data.h"

/* Motor pins ( Enable - In1 - In2 ) */


#define SETSTATES 0  // Set to one if "Enable" pins are set to other pins than 0

/* Limit switch pins */



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
