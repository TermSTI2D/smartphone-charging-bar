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

/* Screw pos infos - Might be changed */
#define POSDOWN 0
#define POSUP 1

#define SecurityDelay 1000

/* Variables */
byte aimedPos = 0;            // Targeted position

byte actualPlatPos = 0;       // Actual position (Or last if it's moving) (From 0 to 3)
int rotCount = 3;
bool isOnLS = true;           // Used to know if the platform is on the limit switch
unsigned long lastUpdate = 0; // Millis() of the last actualPos change (LS Security)

motor ScrewMotor;
motor PlatformMotor;

/* Init function, call one time */
void InitMotors() {
  pinMode(LSUp, INPUT);
  pinMode(LSDown, INPUT);
  pinMode(LSPlatform, INPUT);

  ScrewMotor = motor { ScrewMotorUp, ScrewMotorDown };
  PlatformMotor = motor { PlatformMotorAntiClockwise, PlatformMotorClockwise };

  actualPlatPos = LoadByte(POS_ADDRESS);
  rotCount = LoadByte(ROT_COUNT_ADDRESS);
  
  isOnLS = true;

#if SETSTATES == 1
  SetMotorStates(true);
#endif
}

void SetMotorStates(bool state) {
  digitalWrite(PlatformMotorEnable, state);
  digitalWrite(ScrewMotorEnable, state);
}


/* Main function to call constantly */
void ManageMotors() {
  aimedPos = GetAimedPos();
  
  byte screwPos = aimedPos / 4;
  StayScrewPos(&ScrewMotor, screwPos);
  
  byte platformPos = aimedPos % 4;
  StayPlatformPos(&PlatformMotor, platformPos);
}

// Motor management
void StopMotor(motor *m) {
  digitalWrite(m->forward, LOW);
  digitalWrite(m->backward, LOW);
}

void SetMotor(motor *m, bool forward) {
  byte pin = forward ? m->forward : m->backward;
  byte pstop = forward ? m->backward : m->forward;
  
  digitalWrite(pin, HIGH);
  digitalWrite(pstop, LOW);
}

// Position management
void StayScrewPos(motor *screw, byte pos) {
  // Forward is Up
  
  byte lswitch = (pos == POSUP) ? LSUp : LSDown;
  bool dir = pos == POSUP;

  if (digitalRead(lswitch) == LOW) {
    SetMotor(screw, dir);
    Serial.println("Motor");
  } else {
    StopMotor(screw);
  }
}


byte temp; int left, right; bool forward;
void StayPlatformPos(motor *platform, byte pos) {
  // Forward is Anti clockwise
  pos = 2;
  bool LSState = digitalRead(LSPlatform);

  temp = (actualPlatPos - pos); temp %= 4;
  left = -temp;
  right = 4 - temp;

  if (rotCount + left > 0) {
    forward = false;
  } else if (rotCount + right < 6) {
    forward = true;
  }

  if (LSState && !isOnLS && millis() - lastUpdate > SecurityDelay) {
    actualPlatPos += forward ? 1 : -1;
    actualPlatPos %= 4;
    rotCount += forward ? 1 : -1;

    lastUpdate = millis();

    SaveByte(POS_ADDRESS, actualPlatPos);
    SaveByte(ROT_COUNT_ADDRESS, rotCount);
  }
  
  if (actualPlatPos == pos && isOnLS) {
    StopMotor(platform);
  } else {
    SetMotor(platform, forward);
  }

  isOnLS = LSState;

  Serial.print(rotCount); Serial.print(" ");
  Serial.println(actualPlatPos);
}

bool AreAtRightPlace() {
  return actualPlatPos == GetAimedPos() % 4 && isOnLS;
}
