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
 * Bytes :      2566  / 32256  ( 7%)
 * Variables :  239   / 2048   (11%)
\******************************************/

// Motors
motor Screw;
motor Platform;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting");

  
  InitMotors(Screw, Platform);
  InitManagement();
  
  // For testings
  //delay(1000*2.5);
}


void loop() {
  //ManageMotors(&Screw, &Platform);  // Manage
  delay (10);
}
