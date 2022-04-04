#ifndef DATA_H
#define DATA_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "pins.h"

#define TIMEOUT_DELAY 3000

void InitData();
void CleanTo(char c);
void SaveData(String filename, String data);
String LoadData(String filename, String baseValue);

#endif
