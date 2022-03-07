/******************************************\
 *          Controle des moteurs
 * blablabla
\******************************************/

#include "motors.h"
#include "management.h"

#define LSUp 2
#define LSDown 2
#define LSPlatform 0


#define POSDOWN 0
#define POSUP 1


byte aimedPos = 0;
byte actualPos = 0;
bool isStopped = false;

// MAIN
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

// Functions
void StopMotor(motor *m) {
  digitalWrite(m->forward, LOW);
  digitalWrite(m->backward, LOW);
}

void SetMotor(motor *m, bool forward) {
  StopMotor(m);
  byte pin = forward ? m->forward : m->backward;
  digitalWrite(pin, HIGH);
}

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

  
