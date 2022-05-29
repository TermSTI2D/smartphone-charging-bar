#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "door.h"
#include "keypad.h"
#include "management.h"
#include "motors.h"
#include "pins.h"


#define DEBUG_MODE 0

// Page IDS
#define Homepage 0                // Page d'accueil
#define MoreInformations 1        // Page 'Plus d'informations'

#define ChargeConfirmation 2      // Recharge: confirmation
#define ChargeType 3              // Recharge: Type de charge
#define GetLocation 5             // Recharge: Entrée du mot de passe
#define WaitDoorPage 6             // Recharge: Entrée du mot de passe
#define GoodbyePage 8             // Recharge: Entrée du mot de passe

#define RecoverConfirmation 9
#define TypeID 10

// Passwords
#define TypePassword 4
#define Register 1
#define Confirm 2
#define Recover 3

// Actions
#define NoAction 0
#define WaitForDoor 1

void InitScreen();
void UpdateScreen();

void CallButton(byte pageId, char key);
void SendCommand(String command);
void SendCommand(String prefix, int value, bool guillemet = false);
void SendCommand(String prefix, String value);
void GoToPage(int pageId);
void SendCommandFromSerial();

void StartAddProcedure();
void SelectWireless(bool wireless);
void StartWaitForDoor();

void StartRecoverProcedure();
void ClickID(char id);
void EraseID();
void UpdateID();
void ValidateID();
void OnPassword();

void StartTypePassword();
void AddPassChar(char c);
void EraseChar();
void UpdatePasswordText();
void ConfirmPassword();
void BackPassword();

#endif
