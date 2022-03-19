/* ---------- Define pins ----------- */
// Ecran
#define ScreenRx 0
#define ScreenTx 0
/* ---------- End define pins ----------- */

#include "motors.h"
#include "management.h"
#include "screen.h"

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

#define DEBUG_MODE 1

// Motors
motor Screw;
motor Platform;

#include "data.h"
void setup() {
//#if DEBUG_MODE == 1
  Serial.begin(9600);
  Serial.println("Starting");

  //InitData();
  //SaveData("f"+String(analogRead(A1))+".txt", "position");
//#else
  Serial.begin(9600);
  Serial.println("Starting");

  InitMotors(Screw, Platform);
  InitManagement();
  InitScreen();
//#endif
}


void loop() {
  //ManageMotors(&Screw, &Platform);  // Manage
  
  //SendDataNextion("locAvailable.val=", "5");
  ReceiveDataNextion();
  sendCommandFromSerial();
  delay(10);
}
