#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <Arduino.h>

void InitManagement();

void SetAimedPos(byte newPos);
byte GetAimedPos();

#endif
