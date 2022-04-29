
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


// Valeurs CODE :
// 0 - Alexys
// 1 - Tortue
#define CODE 1

#define DEBUG_MODE 1
#define FINAL_PRINT 1



void setup() {

  Serial.begin(9600);

#if CODE == 0 // Début code Alexys

  InitScreen();
  
#elif CODE == 1 // Début code Tortue

  InitMotors();
  InitManagement();

#elif CODE == 2 // Début code projet final

  Serial.println("Code du projet final")

#endif
}


void loop() {

#if CODE == 0 // Début code Alexys

  ReceiveDataNextion();
  sendCommandFromSerial();
  loop_lower_brightness();

#elif CODE == 1 // Début code Tortue

  //

#elif CODE == 2 // Début code projet final

  Serial.println("Loop projet final");

#endif

  delay(10);
}
