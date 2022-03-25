/****************************************************\
 *          Gestion des téléphones
 * Script non fini
 *  \-> Doit finir le système d'attribution
\****************************************************/

#include "management.h"

byte _aimedPos = 0;

Phone phones[8] = {
  {0, true, "0000"},
  {1, true, "0000"},
  {2, true, "0000"},
  {3, true, "0000"},
  {4, true, "0000"},
  {5, true, "0000"},
  {6, true, "0000"},
  {7, true, "0000"},
};

void InitManagement() {
  // Load data
  //Serial.println( sizeof(Phone) );
  //Serial.println(phones[0].isEmpty);

  LoadPhones();
  //SavePhones();
  for (int i = 0; i < 8; i++) {
    Phone p = phones[i];

    Serial.print(String(i) + ": " + String(p.id) + " " + String(p.isEmpty) + " " + p.password);
    Serial.println("");
  }

  Serial.println("Loaded");
}

void SetAimedPos(byte newPos) {
  _aimedPos = newPos;
}

byte GetAimedPos() {
  return _aimedPos;
}

void LoadPhones() {
  char phonestxt[PHONELINE*8];
  LoadData("phones.txt", "NoData").toCharArray(phonestxt, PHONELINE*8);

  char * line = strtok(phonestxt, "\n");
  
  for (int i = 0; i < 8; i++) {
    // Unpack the data
    char * data = strtok(line, ",");
    phones[i].id = atoi(data);
    
    data = strtok(0, ",");
    phones[i].isEmpty = (bool)atoi(data);
    
    data = strtok(0, ",");
    strcpy(phones[i].password, data);
    
    // Setup next data
    line = strtok(line + PHONELINE, "\n");
    if (line == 0) break;
  }
}

void SavePhones() {
  String phonestxt = "";
  for (int i = 0; i < 8; i++) {
    Phone *p = &phones[i];
    phonestxt += String(p->id) + "," + String(p->isEmpty) + "," + p->password + "\n";// + "," + p->isEmpty + "," + p->password + "\n";
  }

  //Serial.println(phonestxt);
  SaveData("phones.txt", phonestxt);
}

bool RegisterPhone(byte id, String password) {
  Phone *p = &phones[id];

  if (p->isEmpty) {
    p->isEmpty = false;
    password.toCharArray(p->password, 5);
    
    SavePhones();
    return true;
  }
  return false;
}

bool RecoverPhone(byte id) {
  Phone *p = &phones[id];

  if (!p->isEmpty) {
    p->isEmpty = true;
    strcpy(p->password, "0000");
    SavePhones();
    return true;
  }
  return false;
}
