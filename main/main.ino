/* ---------- Define pins ----------- */
// Ecran
#define ScreenRx 0
#define ScreenTx 0

// Moteurs

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
motor Screw;
motor Platform;

void setup() {
  InitMotors(Screw, Platform);



  
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
