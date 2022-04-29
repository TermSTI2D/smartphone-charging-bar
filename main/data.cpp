/****************************************************\
 *          Gestion des donnees
 * SaveByte ( adresse, valeur)
 *    Sauvegarde 1 bit à l'adresse donnee
 *
 * LoadByte ( adresse )
 *    Charge 1 bit à l'adresse donnee
 *
 * SavePhones ( adresse, array, tailleArray )
 *    Sauvegarde la liste de téléphone
 *    
 * LoadPhones ( adresse, array, tailleArray )
 *    Charge la liste de téléphone dans l'array
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
