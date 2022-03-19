#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <SoftwareSerial.h>

void InitScreen();
void searchButton(int pageID,int buttonID);
void ReceiveDataNextion();
void SendDataNextion(String action, String value);
void sendCommandFromSerial();
void Password(byte page);
void addPhone();
void recoverPhone();




#endif
