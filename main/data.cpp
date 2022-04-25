/****************************************************\
 *          Gestion des donnees
 * Initialisation par InitData
 *    Init la carte SD
 *
 * SaveData ( filename, donnees ) <- Necessite la carte SD
 *    Sauvergarde les 'donnees' dans
 *    le fichier nomme 'filename'
 *
 * LoadData( filename, basevalue ) <- Necessite la carte SD
 *    Charge les donnees du fichier
 *    'filename' et renvoie 'basevalue'
 *    si le fichier n'est pas trouvé
\****************************************************/

#include "data.h"

void SaveByte(int adress, byte value) {
  EEPROM.write(adress, value);
}

byte LoadByte(int adress) {
  return EEPROM.read(adress);
}
















SoftwareSerial OpenLog(OpenLogRX, OpenLogTX);
bool isComMode = false;
bool isComReady = false;
bool hasSdCard = false;

void InitData() {
  OpenLog.begin(9600);
  
  // Reset OpenLog
  pinMode(OpenLogReset,OUTPUT);
  digitalWrite(OpenLogReset, LOW);
  delay(100);
  digitalWrite(OpenLogReset, HIGH);

  unsigned long start = millis();
  while(true) {
    if(OpenLog.available()) {
      if (OpenLog.read() == '<') {
        hasSdCard = true;
        break;
      }
    }

    if (millis() - start > TIMEOUT_DELAY) {
      hasSdCard = false;
      break;
    }
  }
  
  OpenLog.setTimeout(150);
}


void CleanTo(char c) {
  if (!hasSdCard) return;
  
  while(true) {
    if(OpenLog.available())
      if (OpenLog.read() == c) break;
  }
}

void GotoCommand() {
  if (!isComMode) {
    // Send 3 escapes to enter OpenLog Command Mode
    OpenLog.write(26); OpenLog.write(26); OpenLog.write(26);
    isComMode = true;
  }

  if (!isComReady) {
    // Wait for '>'
    CleanTo('>');
  } else {
    isComReady = false;
  }
}

void SaveData(String filename, String data) {
  if (!hasSdCard) return;
  
  GotoCommand();
  
  // Recreate the file
  OpenLog.print("rm " + filename + "\r");
  OpenLog.print("new " + filename + "\r");

  // Write data
  OpenLog.print("append " + filename + "\r");

  // Wait to write & Write
  CleanTo('<');
  OpenLog.print(data);
  OpenLog.write('\r');

  isComMode = false;
}

String LoadData(String filename, String baseValue) {
  if (!hasSdCard) return baseValue;
  
  GotoCommand();
  
  // Open & Read the file
  OpenLog.print("read " + filename + "\r");
  
  // Clear command echo
  CleanTo('\r');

  // Return data
  String txt = "";
  if (OpenLog.available()) {
    txt = OpenLog.readString();
  }

  size_t index = txt.lastIndexOf('>');
  if (index != -1) {
    isComReady = true;
    txt.remove(index);
    txt.trim();
  }
  
  return txt;
}
