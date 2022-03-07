#include "management.h"

byte pos = 0;

void SetAimedPos(byte newPos) {
  pos = newPos;
}

byte GetAimedPos() {
  return pos;
}
