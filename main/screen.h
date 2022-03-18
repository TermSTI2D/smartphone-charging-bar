#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <SoftwareSerial.h>

int CommeCa(int parametre); // Pas de définition, juste le nom / parametres
void InitScreen();
void ReceiveDataNextion();
void SendDataNextion(String action, String value);
void sendCommandFromSerial();
void Password(byte page);




#endif
