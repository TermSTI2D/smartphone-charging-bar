#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <Arduino.h>
#include "data.h"
#include "motors.h"

#define PHONELINE 9

#define PHONES_MEMORY 10

struct Phone {
  bool isEmpty : 1;
  char password[5];
};


void InitManagement();

void SetAimedPos(byte newPos);
byte GetAimedPos();

bool RegisterPhone(byte id, String password);
bool RecoverPhone(byte id);

bool IsGoodPassword(byte id, String pass);

byte GetNewPhoneId(bool wireless = false);

void ResetPhones();
void SavePhones();

#endif
