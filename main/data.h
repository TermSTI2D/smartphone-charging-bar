#ifndef DATA_H
#define DATA_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#include "management.h"
#include "motors.h"
#include "pins.h"

#define TIMEOUT_DELAY 3000


void SaveByte(int address, byte value);
byte LoadByte(int address);

void SavePhones(int address, struct Phone phones[], int arraySize);
void LoadPhones(int address, struct Phone phones[], int arraySize);

#endif
