/****************************************************\
 *          Gestion des téléphones
 * SetAimedPos ( pos ) ; GetAimedPos( void )
 *    Gestion de la position des moteurs
 *    
 * RegisterPhone ( id, password )
 *    Enregistre un telephone avec
 *    le mot de passe fourni
 *    
 * RecoverPhone ( id )
 *    Reset l'emplacement du telephone
 *    a l'id donnee
 * 
 * GetNewPhoneId ( wireless ? )
 *    Donne un ID libre en fonction
 *    de la demande
\****************************************************/

#include "management.h"

byte _aimedPos = 0;

Phone phones[8] = {
  { true, "0000" },
  { true, "1324" },
  { true, "5678" },
  { true, "9070" },
  { true, "0000" },
  { true, "0000" },
  { true, "0000" },
  { true, "0000" },
};



void InitManagement() {
  LoadPhones(PHONES_MEMORY, phones, sizeof(phones));
}

void SetAimedPos(byte newPos) {
  _aimedPos = newPos;
}

byte GetAimedPos() {
  return _aimedPos;
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

bool IsGoodPassword(byte id, String pass) {
  String phonePass = String(phones[id].password);
  return phonePass == pass;
}

byte GetNewPhoneId(bool wireless) {
  int id = wireless ? 3 : 7;
  
  for (; id >= 0; id--) {
    if (phones[id].isEmpty) {
      return id;
    }
  }

  return -1;
}

void ResetPhones() {
  for (byte i = 0; i < 8; i++) {
    RecoverPhone(i);
  }

  SavePhones();
}

void SavePhones() {
    SavePhones(PHONES_MEMORY, phones, sizeof(phones));
}
