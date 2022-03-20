#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <Arduino.h>
#include "data.h"

#define PHONELINE 9

struct Phone {
  byte id : 3;
  bool isEmpty : 1;
  char password[5];
};


void InitManagement();

void SetAimedPos(byte newPos);
byte GetAimedPos();

void LoadPhones();
void SavePhones();

bool RegisterPhone(byte id, String password);
bool RecoverPhone(byte id);

#endif
