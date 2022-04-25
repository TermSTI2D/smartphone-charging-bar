#ifndef DATA_H
#define DATA_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#include "motors.h"
#include "pins.h"

#define TIMEOUT_DELAY 3000

void InitData();
void CleanTo(char c);
void SaveData(String filename, String data);
String LoadData(String filename, String baseValue);

void SaveByte(int address, byte value);
byte LoadByte(int address);

#endif
