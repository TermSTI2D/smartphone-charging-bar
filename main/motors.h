#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include "pins.h"
#include "data.h"
#include "management.h"

#define POS_ADDRESS 0
#define ROT_COUNT_ADDRESS 1

#define SETSTATES 0  // Set to one if "Enable" pins are set to other pins than 0


struct motor {
  byte forward;
  byte backward;
};

void InitMotors();
void SetMotorStates(bool state);
void ManageMotors();

void StopMotor(motor *m);
void SetMotor(motor *m, bool forward);

void StayScrewPos(motor *screw, byte pos);
void StayPlatformPos(motor *platform, byte pos);

bool AreAtRightPlace();

#endif
