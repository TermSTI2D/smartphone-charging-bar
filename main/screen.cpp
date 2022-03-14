#include "screen.h"
SoftwareSerial nextionSerial(10, 11); // RX, TX

int CommeCa(int paremetre) { // Meme signature (nom / parametres) mais on déclare un corps
  return 1546;
}

void init(){
  Serial.begin(9600);
  Serial.print("Serial port has been set to 9600")
  nextionSerial.begin(9600);
  Serial.print("nextionSerial port has been set to 9600")
}
