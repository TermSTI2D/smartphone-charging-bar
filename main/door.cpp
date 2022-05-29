#include "door.h"

void InitDoor() {
  pinMode(ElectroMagnet, OUTPUT);
}

void OpenDoor() {
  digitalWrite(ElectroMagnet, LOW);
}

void CloseDoor() {
  digitalWrite(ElectroMagnet, HIGH);
}
