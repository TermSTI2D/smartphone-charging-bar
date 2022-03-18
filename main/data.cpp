#include "data.h"

SoftwareSerial OpenLog(OpenLogRX, OpenLogTX);
bool isComMode = false;
bool isComReady = false;

void InitData() {
  OpenLog.begin(9600);
  
  // Reset OpenLog
  pinMode(OpenLogReset,OUTPUT);
  digitalWrite(OpenLogReset, LOW);
  delay(100);
  digitalWrite(OpenLogReset, HIGH);

 /* while (1) {
    int v = OpenLog.read();
    if (v == '<') break;
    Serial.write(v);
  }*/

  CleanTo('<');

  Serial.println("IC");
  OpenLog.println("Initialisation complete");
}


void CleanTo(char c) {
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

String LoadData(String filename) {
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

  txt.remove(txt.indexOf('>'));
  txt.trim();
  
  return txt;
}
