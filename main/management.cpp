#include "management.h"
#include "data.h"

byte pos = 0;


void InitManagement() {
  // Load data
}

void SetAimedPos(byte newPos) {
  pos = newPos;
}

byte GetAimedPos() {
  return pos;
}
