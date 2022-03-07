/* ---------- Define pins ----------- */
// Ecran
#define ScreenRx 0
#define ScreenTx 0

// Moteurs
#define ScrewMotorEnable 0
#define ScrewMotorUp 4
#define ScrewMotorDown 5

#define PlatformMotorEnable 0
#define PlatformMotorForward 0
#define PlatformMotorBackward 0
/* ---------- End define pins ----------- */

#include "motors.h"
#include "management.h"

/******************************************\
 *          How program work
 * blablabla
 * blablabla
 * blabla
 * bla
 * blalalamabla
\******************************************/

// Motors
motor Screw { ScrewMotorUp, ScrewMotorDown };
motor Platform { PlatformMotorForward, PlatformMotorBackward };

void setup() {
  SetAimedPos(0);
  
  Serial.begin(9600);
  delay(1000*2.5);
  Serial.println("Starting");
}


void loop() {
  ManageMotors(&Screw, &Platform);
  delay(1000);
  Serial.println(millis());
  SetAimedPos((GetAimedPos() + 1) % 8);
}
