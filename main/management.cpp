#include "management.h"
#include "data.h"

byte pos = 0;
phone *phones;

void InitManagement() {
  phones = LoadPhones();
}

void SetAimedPos(byte newPos) {
  pos = newPos;
}

byte GetAimedPos() {
  return pos;
}
