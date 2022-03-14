#include <SoftwareSerial.h>
#include "screen.h"

SoftwareSerial nextionSerial(10, 11); // RX, TX

int CommeCa(int paremetre) { // Meme signature (nom / parametres) mais on déclare un corps
  return 1546;
}

void InitScreen(){
  Serial.println("--------------------------");
  Serial.begin(9600);
  Serial.println("Serial port has been set to 9600");
  Serial.println("--------------------------");
  nextionSerial.begin(9600);
  Serial.println("nextionSerial port has been set to 9600");
}

void ReceiveDataNextion(){
  if (nextionSerial.available()){
    Serial.write("Received : " + nextionSerial.read());
  }
}

void SendDataNextion(String action, String value){
  nextionSerial.print(action);
  nextionSerial.print(value);
  nextionSerial.print(0xff);
  nextionSerial.print(0xff);
  nextionSerial.print(0xff);
  //Serial log
  Serial.println("Sent : " + action + value + "\"");
}

/******************************************\
 *          Password type page
 * 1 : create
 * 2 : confirm
 * 3 : verify (recover smartphone)
\******************************************/
void Password(byte page){
  if(page==1){

  } else if(page==2){

  } else if(page==3){

  } else{
    //Page not found
    //Add eror page and error code
  }
}
