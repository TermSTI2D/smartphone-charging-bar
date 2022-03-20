#include <SoftwareSerial.h>
#include "screen.h"

// Variables
int messageReceived[7] = {};
String commandFromSerial = ""; 
bool passwordConfirmation = false;
String writePasswordVar = "";
#define buttonsLine 1
#define buttonsColumn 3

struct Button {
  byte pageId;
  byte buttonId;
  void (*button_func) (void);
};

Button buttons[] = {
  { 0, 3, []() { SendDataNextion("page", "2"); } }, //Btn (Recharger son smartphone)
  { 2, 2, []() { SendDataNextion("page", "3"); } }, //Btn (Ajouter son smartphone)
  { 3, 2, []() { addPhone("wireless"); } }, //Btn (Recharge sans fil)
  { 3, 3, []() { addPhone("cable"); } }, //Btn (Recharge filaire)
  { 4, 2, []() { passwordConfirmation = true; } }, //Btn (Valider : Page ajouter un code)
  { 4, 3, []() { writePassword("erase"); } }, //Btn (Effacer : Page ajouter un code)
  { 4, 4, []() { writePassword("0"); } }, //Btn (0 : Page ajouter un code)
  { 4, 5, []() { writePassword("1"); } }, //Btn (1 : Page ajouter un code)
  { 4, 6, []() { writePassword("2"); } }, //Btn (2 : Page ajouter un code)
};

size_t bsize = sizeof(buttons) / sizeof(Button);



// char buttons[buttonsLine][buttonsColumn] = { //[Lignes][Colones]
//   {'0','3','SendDataNextion(page, 2)'} //Page ID, Button ID, Function
// };

SoftwareSerial  nextionSerial(10, 11); // RX, TX

void InitScreen(){
  Serial.println("--------------------------");
  Serial.begin(9600);
  Serial.println("Serial port has been set to 9600");
  Serial.println("--------------------------");
  nextionSerial.begin(9600);
  Serial.println("nextionSerial port has been set to 9600");
  SendDataNextion("page", "0");
}

//Search button
void searchButton(int pageId,int buttonId){
  Serial.println("");
  Serial.println("Search page " + String(pageId) + " and button " + String(buttonId));
  for (size_t i = 0; i < bsize; i++) {
    if (buttons[i].pageId == pageId && buttons[i].buttonId == buttonId) {
      buttons[i].button_func();
    }
  }
}

void ReceiveDataNextion(){
  if  (nextionSerial.available()){
    delay(100);
    for (int i = 0; i < 7; i++) {
      messageReceived[i] = nextionSerial.read();
    }
    // Serial log
    Serial.println("");
    Serial.println("Received : ");
    for (int i = 0; i < 7; i++) {
      Serial.print("   Data" + String(i) + " : " + messageReceived[i]);
    }
    delay(100);
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

/******************************************\
 *          Password type page
 * 1 : create
 * 2 : confirm
 * 3 : verify (recover smartphone)
\******************************************/

String Password(int page){
  writePasswordVar = " ";
  writePassword("erase");
  switch (page) {
    case 1:
      //Create password
      SendDataNextion("page", "4");
      break;
    case 2:
      //Confirm password
      SendDataNextion("page", "5");
      break;
    case 3:
      //Verify password
      SendDataNextion("page", "13");
      break;
  }
  // while(!passwordConfirmation && writePasswordVar.length() != 4){
  //   ReceiveDataNextion();
  //   delay(10);
  // }
  passwordConfirmation == false;
  return writePasswordVar;
}

String writePassword(String actionOrNumber){
  delay(100);
  if(actionOrNumber == "erase"){
    int length=writePasswordVar.length();
    writePasswordVar.setCharAt(length-1,'\t');
    writePasswordVar.trim();
    SendDataNextion("password.txt=", "\"" + writePasswordVar + "\"");
  }
  else{
    delay(100);
    writePasswordVar = writePasswordVar + actionOrNumber;
    delay(100);
    delay(100);
    //SendDataNextion("password.txt=", "\"" + writePasswordVar + "\"");
    delay(100);
  }
}


//Function AddPhone
//Type : wireless, cable
void addPhone(String type){
  String password = "";
  password = Password(1);
}

//Function RecoverPhone
void recoverPhone(){

}
