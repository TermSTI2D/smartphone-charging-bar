#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <SoftwareSerial.h>

void InitScreen();
void searchButton(int pageID,int buttonID);
void ReceiveDataNextion();
void SendDataNextion(String action, String value);
void sendCommandFromSerial();
void writePassword(String actionOrNumber);
void addPhone(String type);
void recoverPhone();




#endif
