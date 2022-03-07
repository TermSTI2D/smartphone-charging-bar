/* ---------- Define pins ----------- */
// Ecran
#define ScreenRx 0
#define ScreenTx 0
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

/******************************************\
 *          Compiled infos
 * Bytes :      2488  /32256  ( 7%)
 * Variables :  235   / 2048  (11%)
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
  //SetAimedPos((GetAimedPos() + 1) % 8);
}
