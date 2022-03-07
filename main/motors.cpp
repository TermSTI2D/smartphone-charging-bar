/******************************************\
 *          Controle des moteurs
 * blablabla
\******************************************/

#include "motors.h"
#include "management.h"

/* Motor pins ( Enable - In1 - In2 ) */
#define ScrewMotorEnable 0
#define ScrewMotorUp 4
#define ScrewMotorDown 5

#define PlatformMotorEnable 0
#define PlatformMotorForward 0
#define PlatformMotorBackward 0

/* Limit switch pins */
#define LSUp 2
#define LSDown 2
#define LSPlatform 0

/* Screw pos infos - Might be changed */
#define POSDOWN 0
#define POSUP 1

/* Variables */
byte aimedPos = 0;    // Targetted position
byte actualPos = 0;   // Actual position (Or last if it's moving)
bool isOnLS = false;  // Used to know if the platform is on the limit switch


/* Init function, call one time */
void InitMotors(motor & screw, motor & platform) {
  SetAimedPos(0);

  screw = motor { ScrewMotorUp, ScrewMotorDown };
  platform = motor { PlatformMotorForward, PlatformMotorBackward };

  // SetMotorStates(true);
}

void SetMotorStates(bool state) {
  digitalWrite(PlatformMotorEnable, state);
  digitalWrite(ScrewMotorEnable, state);
}


/* Main function to call constantly */
void ManageMotors(motor *screw, motor *platform) {
  //*
  aimedPos = GetAimedPos();
  
  byte screwPos = aimedPos / 4;
  StayScrewPos(screw, screwPos);
  
  byte platformPos = aimedPos % 4;
  StayPlatformPos(platform, platformPos);
  //*/

  
  
  //Serial.println("Manage");
  //SetMotor(screw, false);
  //Serial.println(screw->forward);
  
  
  //byte screwpos = (aimedPos / 4 == 0) ? POSDOWN : POSUP;
  //StayScrewPos(screw, screwpos);
  
}

// Motor management
void StopMotor(motor *m) {
  digitalWrite(m->forward, LOW);
  digitalWrite(m->backward, LOW);
}

void SetMotor(motor *m, bool forward) {
  StopMotor(m);
  byte pin = forward ? m->forward : m->backward;
  digitalWrite(pin, HIGH);
}

// Position management
void StayScrewPos(motor *screw, byte pos) {
  byte lswitch = (pos == POSUP) ? LSUp : LSDown;
  bool dir = pos == POSUP;

  if (digitalRead(lswitch) == LOW) {
    SetMotor(screw, dir);
  } else {
    StopMotor(screw);
  }
}

void StayPlatformPos(motor *platform, byte pos) {
  Serial.println("Not implemented");
  return;
  //byte pos = aimedPos % 4;

  if (actualPos % 4 != pos) {
      
  }
}

  
