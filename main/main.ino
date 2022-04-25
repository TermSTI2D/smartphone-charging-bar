
/* ---------- End define pins ----------- */

#include "motors.h"
#include "management.h"
#include "screen.h"
#include "data.h"

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
 * Bytes :      7378  / 32256  (22%)
 * Variables :  564   / 2048   (27%)
\******************************************/

#define DEBUG_MODE 1
#define FINAL_PRINT 1



void setup() {
#if DEBUG_MODE == 1
  Serial.begin(9600);
  InitMotors();
  InitScreen();  
#elif
  // Code du projet final

#if FINAL_PRINT == 1
  Serial.begin(9600);
  Serial.println("Starting");
#endif

  // Inits
  InitData();
  InitMotors();
  InitManagement();
  InitScreen();
#endif
}


void loop() {
  //ManageMotors(&Screw, &Platform);  // Manage
  
  //SendDataNextion("locAvailable.val=", "5");
  ReceiveDataNextion();
  sendCommandFromSerial();
  loop_lower_brightness();
  delay(10);
}