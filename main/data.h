#ifndef DATA_H
#define DATA_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#define OpenLogRX 10
#define OpenLogTX 3
#define OpenLogReset 4


void InitData();
void CleanTo(char c);
void SaveData(String filename, String data);
String LoadData(String filename);

#endif
