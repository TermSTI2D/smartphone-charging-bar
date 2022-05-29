#include <SoftwareSerial.h>
#include "screen.h"
#include "pins.h"


SoftwareSerial screenSerial(ScreenRx, ScreenTx);
int currentPage = 0;
int currentAction = NoAction;

int currentPassIndex = 0;
char curPass[5] = "    ";
int passFor = 0;

struct Button {
  byte pageId;
  char key;
  void (*on_call) (void);
};

Button buttons[] = {
  { Homepage, 'A', []() { GoToPage(ChargeConfirmation); } },      // Rechager son smartphone
  { Homepage, 'B', []() { GoToPage(RecoverConfirmation); } },      // Recuperer son smartphone

  { ChargeConfirmation, 'A', []() { StartAddProcedure(); } },     // Confirmation de recharge
  { ChargeConfirmation, 'C', []() { GoToPage(Homepage); } },      // Retour à l'accueil
  
  { RecoverConfirmation, 'A', []() { StartRecoverProcedure(); } },     // Confirmation de recuperation
  { RecoverConfirmation, 'C', []() { GoToPage(Homepage); } },      // Retour à l'accueil

  { ChargeType, 'A', []() { SelectWireless(true); } },            // Recharge sans fils
  { ChargeType, 'B', []() { SelectWireless(false); } },           // Recharge filaire
  { ChargeType, 'C', []() { GoToPage(Homepage); } },              // Retour à l'accueil

  { TypePassword, 'A', []() { ConfirmPassword(); } },            // Valide le mot de passe
  { TypePassword, 'B', []() { EraseChar(); } },                  // Efface un caractère du mdp
  { TypePassword, 'C', []() { BackPassword(); } },         // Retour page
  { TypePassword, '0', []() { AddPassChar('0'); } },             // Ajoute un caractère au mdp
  { TypePassword, '1', []() { AddPassChar('1'); } },             // Ajoute un caractère au mdp
  { TypePassword, '2', []() { AddPassChar('2'); } },             // Ajoute un caractère au mdp
  { TypePassword, '3', []() { AddPassChar('3'); } },             // Ajoute un caractère au mdp
  { TypePassword, '4', []() { AddPassChar('4'); } },             // Ajoute un caractère au mdp
  { TypePassword, '5', []() { AddPassChar('5'); } },             // Ajoute un caractère au mdp
  { TypePassword, '6', []() { AddPassChar('6'); } },             // Ajoute un caractère au mdp
  { TypePassword, '7', []() { AddPassChar('7'); } },             // Ajoute un caractère au mdp
  { TypePassword, '8', []() { AddPassChar('8'); } },             // Ajoute un caractère au mdp
  { TypePassword, '9', []() { AddPassChar('9'); } },             // Ajoute un caractère au mdp

  { TypeID, 'A', []() { ValidateID(); } },                      // Valide le mot de passe
  { TypeID, 'B', []() { EraseID(); } },                  // Efface un caractère du mdp
  { TypeID, 'C', []() { GoToPage(Homepage); } },         // Retour page
  { TypeID, '1', []() { ClickID('1'); } },             // Ajoute un caractère au mdp
  { TypeID, '2', []() { ClickID('2'); } },             // Ajoute un caractère au mdp
  { TypeID, '3', []() { ClickID('3'); } },             // Ajoute un caractère au mdp
  { TypeID, '4', []() { ClickID('4'); } },             // Ajoute un caractère au mdp
  { TypeID, '5', []() { ClickID('5'); } },             // Ajoute un caractère au mdp
  { TypeID, '6', []() { ClickID('6'); } },             // Ajoute un caractère au mdp
  { TypeID, '7', []() { ClickID('7'); } },             // Ajoute un caractère au mdp
  { TypeID, '8', []() { ClickID('8'); } },             // Ajoute un caractère au mdp
  
  { GetLocation, 'A', []() { StartWaitForDoor(); } },                   // Ajoute un caractère au mdp
  { GoodbyePage, 'A', []() { GoToPage(Homepage); } },              // Ajoute un caractère au mdp
  
};

size_t bsize = sizeof(buttons) / sizeof(Button);


void InitScreen(){
  screenSerial.begin(9600);
  GoToPage(Homepage);
  //SendCommand("dims", "100");
}

void UpdateScreen() {

  if (currentAction == NoAction) {
    char pressed = GetPressed();
    if (pressed) {
      CallButton(currentPage, pressed);
    }
  } else if (currentAction == WaitForDoor) {
    if (AreAtRightPlace()) {
      OpenDoor();
      delay(150);
      CloseDoor();
      
      currentAction = NoAction;
      GoToPage(GoodbyePage);
    }
  }

  
}

void CallButton(byte pageId, char key) {

  for (size_t index = 0; index < bsize; index++) {
    if (buttons[index].pageId == pageId && buttons[index].key == key) {
      buttons[index].on_call();
      break;
    }
  }  
}

void SendCommand(String command) {

#if DEBUG_MODE == 0
  screenSerial.print(command);

  screenSerial.write(0xff);
  screenSerial.write(0xff);
  screenSerial.write(0xff);
#elif DEBUG_MODE == 1
  Serial.print(command);

  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
#endif

}

void SendCommand(String prefix, int value, bool guillemet) {
  if (guillemet) {
    SendCommand(prefix + "=\"" + String(value) + "\"");
  } else {
    SendCommand(prefix + "=" + String(value));
  }
}

void SendCommand(String prefix, String value) {
  SendCommand(prefix + "=\"" + value + "\"");
}

void GoToPage(int pageId) {
  SendCommand("page " + String(pageId));
  currentPage = pageId;

  //Serial.println("Now on page: " + String(pageId));
}

void SendCommandFromSerial() {
  if (Serial.available()) {
    String commandFromSerial = Serial.readString();
    commandFromSerial.trim();
    SendCommand(commandFromSerial);
  }
}





// AddPhone procedure

struct AddPhone {
  bool wireless;
  byte id;
  char password[5];
};

AddPhone currentAdd = { false, 0, "0000" };

void StartAddProcedure() {
  currentAdd.wireless = false;
  currentAdd.id = 0;
  strcpy(currentAdd.password, "    ");
  
  currentPassIndex = 0;
  GoToPage(ChargeType);
}

void SelectWireless(bool wireless) {
  currentAdd.wireless = wireless;

  passFor = Register;
  StartTypePassword();

  currentAdd.id = GetNewPhoneId(wireless);
  SetAimedPos(currentAdd.id);
}


void StartWaitForDoor() {
  //Serial.println(currentAdd.id);
  //Serial.println(currentAdd.password);
  
  GoToPage(WaitDoorPage);
  currentAction = WaitForDoor;

  RegisterPhone(currentAdd.id, String(currentAdd.password));
}





// Recover phone procedure

struct RecoverPhone {
  char id;
  char password[5];
};

struct RecoverPhone currentRec = { ' ', "    " };

void StartRecoverProcedure() {
  currentRec.id = ' ';
  strcpy(currentRec.password, "    ");
  
  GoToPage(TypeID);
}

void ClickID(char id) {
  if (currentRec.id == ' ') {
    currentRec.id = id;
  }
  
  UpdateID();
}

void EraseID() {
  currentRec.id = ' ';
  UpdateID();
}

void UpdateID() {
  //Serial.println(currentRec.id);
  SendCommand("idTxt.txt", String(currentRec.id));
}

void ValidateID() {
  if (currentRec.id != ' ') {
    passFor = Recover;
    StartTypePassword();
  }
}

void OnPassword() {
  byte id = (byte)(currentRec.id - '0');
  if (IsGoodPassword(id, String(curPass))) {
    SetAimedPos(id);
    StartWaitForDoor();
  } else {
    SendCommand("errorMessage.txt", "Mot de passe ou ID incorrecte");
  }
}





// Type Password
void StartTypePassword() {
  GoToPage(TypePassword);
  currentPassIndex = 0;
  strcpy(curPass, "    ");
  UpdatePasswordText();
}

void AddPassChar(char c) {
  if (currentPassIndex <= 3) {
    curPass[currentPassIndex++] = c;
  }

  UpdatePasswordText();
}

void EraseChar() {
  if (currentPassIndex > 0) {
    curPass[--currentPassIndex] = ' ';
  }
  
  UpdatePasswordText();
}

void UpdatePasswordText() {
  SendCommand("passwordTxt.txt", String(curPass));
  //Serial.println(curPass);
}

void ConfirmPassword() {
  if (currentPassIndex == 4) {
    switch (passFor) {
      case Register:
        GoToPage(GetLocation);
        delay(10);
        SendCommand("id.val", currentAdd.id);
        strcpy(currentAdd.password, curPass);
        break;
      case Recover:
        OnPassword();
        break;
    }
  } else {
    SendCommand("errorMessage.txt", "Votre code doit disposer de 4 chiffres");
  }
}

void BackPassword() {
  switch(passFor) {
    case Register:
      GoToPage(ChargeType);
      break;
    case Recover:
      GoToPage(TypeID);
      break;
  }
}
