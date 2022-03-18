#include "management.h"
#include "data.h"

byte _aimedPos = 0;

void InitManagement() {
  // Load data
}

void SetAimedPos(byte newPos) {
  _aimedPos = newPos;
}

byte GetAimedPos() {
  return _aimedPos;
}
