/****************************************************\
 *          Controle des moteurs
 * Initialisation des moteurs par InitMotors
 *    Donne les bons pins
 *    Enclenche les moteurs
 *    Charge la position actuelle
 * 
 * Action continue par ManageMotors
 *    Va au bon emplacement à l'aide des fonctions
 *      - StayScrewPos
 *      - StayPlatformPos
 * 
 * StayScrewPos
 *    Emmene la vis en haut (Pos 1)
 *    ou en bas (Pos 2) et y reste
 * 
 *    
 * StayPlatformPos
 *    Place la plateforme au bon
 *    emplacement (De 1 à 4) et y reste
\****************************************************/

#include "motors.h"
#include "management.h"

/* Motor pins ( Enable - In1 - In2 ) */
#define ScrewMotorEnable 0
#define ScrewMotorUp 4
#define ScrewMotorDown 5

#define PlatformMotorEnable 0
#define PlatformMotorAntiClockwise 0
#define PlatformMotorClockwise 0

/* Limit switch pins */
#define LSUp 2
#define LSDown 2
#define LSPlatform 0

/* Screw pos infos - Might be changed */
#define POSDOWN 0
#define POSUP 1

#define SecurityDelay 1000

/* Variables */
byte aimedPos = 0;            // Targeted position

byte actualPlatPos = 0;       // Actual position (Or last if it's moving)
bool isOnLS = true;           // Used to know if the platform is on the limit switch
unsigned long lastUpdate = 0; // Millis() of the last actualPos change (LS Security)


/* Init function, call one time */
void InitMotors(motor & screw, motor & platform) {
  SetAimedPos(0);

  screw = motor { ScrewMotorUp, ScrewMotorDown };
  platform = motor { PlatformMotorAntiClockwise, PlatformMotorClockwise };

  // Load the actualPlatPosition ( & Aimed position? )
  
  isOnLS = true;
  
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

  //testings
  
  
  
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
  // Forward is Up
  
  byte lswitch = (pos == POSUP) ? LSUp : LSDown;
  bool dir = pos == POSUP;

  if (digitalRead(lswitch) == LOW) {
    SetMotor(screw, dir);
  } else {
    StopMotor(screw);
  }
}

void StayPlatformPos(motor *platform, byte pos) {
  // Forward is Anti clockwise

  bool LSState = digitalRead(LSPlatform);
  
  // Find shortest path
  bool forward = true;
  Serial.println("Not implemented shortest path");

  // Update actualPos
  if (LSState && !isOnLS && millis() - lastUpdate > SecurityDelay) {
    actualPlatPos += forward ? 1 : -1;
    lastUpdate = millis();
  }


  // Go to the targeted position
  byte current = actualPlatPos % 4;
  if (current != pos || !isOnLS) {
    SetMotor(platform, forward);
  } else {
    StopMotor(platform);
  }
  
  isOnLS = LSState;
}
