#include <SoftwareSerial.h>
#include "screen.h"

// Variables
int messageReceived[7] = {};
String commandFromSerial = ""; 

#define buttonsLine 1
#define buttonsColumn 3

char buttons[buttonsLine][buttonsColumn] = { //[Lignes][Colones]
  {'0','3','SendDataNextion(page, 2)'} //Page ID, Button ID, Function
};

SoftwareSerial  nextionSerial(10, 11); // RX, TX

void InitScreen(){
  Serial.println("--------------------------");
  Serial.begin(9600);
  Serial.println("Serial port has been set to 9600");
  Serial.println("--------------------------");
  nextionSerial.begin(9600);
  Serial.println("nextionSerial port has been set to 9600");
}

//Search button
void searchButton(int pageID,int buttonID){
  Serial.println("");
  Serial.println("Search page " + String(pageID) + " and button " + String(buttonID));
  for(int i = 0; i < buttonsLine; i++){
    //search line when pageID and buttonID are in same line
    if(String(buttons[i][0]) == String(pageID) && String(buttons[i][1]) == String(buttonID)){
      Serial.println("Button found");
      //Print text in column 2
      Serial.println("Text to send : " + String(buttons[i][2]));
    }
  }
}

void ReceiveDataNextion(){
  delay(100);
  if  (nextionSerial.available()){
    for (int i = 0; i < 7; i++) {
      messageReceived[i] = nextionSerial.read();
    }
    // Serial log
    Serial.println("");
    Serial.println("Received : ");
    for (int i = 0; i < 7; i++) {
      Serial.print("   Data" + String(i) + " : " + messageReceived[i]);
    }
    if(messageReceived[0]==101){
      searchButton(messageReceived[1],messageReceived[2]);
    }
  }
}

void SendDataNextion(String action, String value){
  if(action == "page"){
    nextionSerial.print(action + " " + value);
  }
  else{
    nextionSerial.print(action);
    nextionSerial.print(value);
  }
  nextionSerial.write(0xff);
  nextionSerial.write(0xff);
  nextionSerial.write(0xff);
  //Serial log
  Serial.println("Sent : " + action + value + "\"");
}

void sendCommandFromSerial(){
  if (Serial.available()) {
    Serial.println("");
    Serial.print("Command sent from Serial : ");
    // Save search command in variable
    commandFromSerial = Serial.readString();
    Serial.println(commandFromSerial);
    // Data processing
    // Separate command and value (with spaec)
    String command = commandFromSerial.substring(0, commandFromSerial.indexOf(" "));
    String value = commandFromSerial.substring(commandFromSerial.indexOf(" ") + 1);
    // Delete spaces
    command.trim();
    value.trim();
    // Send data to Nextion
    SendDataNextion(command, value);
  }
}


//Function AddPhone
void addPhone(){

}

//Function RecoverPhone
void recoverPhone(){

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
