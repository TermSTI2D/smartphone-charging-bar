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
    
    SavePhones(PHONES_MEMORY, phones, sizeof(phones));
    return true;
  }
  return false;
}

bool RecoverPhone(byte id) {
  Phone *p = &phones[id];

  if (!p->isEmpty) {
    p->isEmpty = true;
    strcpy(p->password, "0000");
    SavePhones(PHONES_MEMORY, phones, sizeof(phones));
    return true;
  }
  return false;
}
