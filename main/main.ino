
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

void ResetMemory() {
  // Motors
  SaveByte(POS_ADDRESS, 0);
  SaveByte(ROT_COUNT_ADDRESS, 3);

  // Phones
  ResetPhones();
}

void setup() {
  Serial.begin(9600);

  ResetMemory();
  
  InitDoor();
  InitManagement();
  InitMotors();
  InitScreen();

  CloseDoor();
}

void loop() {
  if (digitalRead(4) == HIGH) {
    //Serial.println("High");
  }
  
  ManageMotors();
  UpdateScreen();
  delay(10);
}
