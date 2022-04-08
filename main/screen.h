#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "pins.h"


void InitScreen();
void searchButton(int pageID,int buttonID);
void ReceiveDataNextion();
void SendDataNextion(String action, String value);
void sendCommandFromSerial();
void writePassword(String actionOrNumber);
void writeId(String actionOrNumber);
bool allCharactersSame(String s);
void validatePassword();
void confirmPassword();
void confirmId();
void addPhone(String type);
void recoverPhone();
void recoveryProcess();
void showLastPages(byte action);
void endProcess();
void popup(int action, String pass);
void loop_lower_brightness();



#endif
