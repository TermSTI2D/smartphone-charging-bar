#include <SoftwareSerial.h>
#include "screen.h"

SoftwareSerial nextionSerial(10, 11); // RX, TX

int CommeCa(int paremetre) { // Meme signature (nom / parametres) mais on déclare un corps
  return 1546;
}

void InitScreen(){
  Serial.begin(9600);
  Serial.println("Serial port has been set to 9600");
  nextionSerial.begin(9600);
  Serial.println("nextionSerial port has been set to 9600 tets");
}

void ReceiveDataNextion(){
  if (nextionSerial.available()){
    Serial.write(nextionSerial.read());
  }
}

/******************************************\
 *          Password type page
 * 1 : create
 * 2 : confirm
 * 3 : verify (recover smartphone)
\******************************************/
void Password(int page){
  if(page==1){

  }
  else if(page==2){

  }
  else if(page==3){

  }
  else{
    //Page not found
    //Add eror page and error code
  }
}
