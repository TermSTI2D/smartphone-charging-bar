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

void SaveByte(int address, byte value) {
  EEPROM.write(address, value);
}

byte LoadByte(int address) {
  return EEPROM.read(address);
}


void SavePhones(int address, Phone phones[], int arraySize) {
  byte phoneSize = sizeof(Phone);
  byte amount = arraySize / phoneSize;
  
  for (byte a = 0; a < amount; a++) {
    EEPROM.put(a * phoneSize, phones[a]);
  }
}

void LoadPhones(int address, Phone phones[], int arraySize) {
  byte phoneSize = sizeof(Phone);
  byte amount = arraySize / phoneSize;

  for (byte a = 0; a < amount; a++) {
    EEPROM.get(a * phoneSize, phones[a]);
  }
}
