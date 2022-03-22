#include <SoftwareSerial.h>
#include "screen.h"

// Variables
int messageReceived[7] = {};
String commandFromSerial = ""; 
String password = "";
// Add Smartphone
String writePasswordVar = "";
String type = "";

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
  { 4, 2, []() { validatePassword(); } }, //Btn (Valider : Page ajouter un code) // A améliroer
  { 4, 3, []() { writePassword("erase"); } }, //Btn (Effacer : Page ajouter un code)
  { 4, 4, []() { writePassword("0"); } }, //Btn (0 : Page ajouter un code)
  { 4, 5, []() { writePassword("1"); } }, //Btn (1 : Page ajouter un code)
  { 4, 6, []() { writePassword("2"); } }, //Btn (2 : Page ajouter un code)
  { 4, 7, []() { writePassword("3"); } }, //Btn (3 : Page ajouter un code)
  { 4, 8, []() { writePassword("4"); } }, //Btn (4 : Page ajouter un code)
  { 4, 9, []() { writePassword("5"); } }, //Btn (5 : Page ajouter un code)
  { 4, 10, []() { writePassword("6"); } }, //Btn (6 : Page ajouter un code)
  { 4, 11, []() { writePassword("7"); } }, //Btn (7 : Page ajouter un code)
  { 4, 12, []() { writePassword("8"); } }, //Btn (8 : Page ajouter un code)
  { 4, 13, []() { writePassword("9"); } }, //Btn (9 : Page ajouter un code)
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
      break;
    }
  }
}

void ReceiveDataNextion(){
  if  (nextionSerial.available()){
    delay(10);
    for (int i = 0; i < 7; i++) {
      messageReceived[i] = nextionSerial.read();
    }
    // Serial log
    Serial.println("");
    Serial.println("Received : ");
    for (int i = 0; i < 7; i++) {
      Serial.print("   Data" + String(i) + " : " + messageReceived[i]);
    }
    delay(10);
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

// Write password
void writePassword(String actionOrNumber){
    if(actionOrNumber == "erase"){
      int length=writePasswordVar.length();
      writePasswordVar.setCharAt(length-1,'\t');
      writePasswordVar.trim();
      SendDataNextion("passwordTxt.txt=", "\"" + writePasswordVar + "\"");
    }
    else if(writePasswordVar.length() < 4){
      writePasswordVar = writePasswordVar + actionOrNumber;
      SendDataNextion("passwordTxt.txt=", "\"" + writePasswordVar + "\"");
    }
}

// Validate password
void validatePassword(){
  if(writePasswordVar.length() < 4){
    SendDataNextion("errorMessage.txt=", "\"Votre code doit disposer de 4 chiffres.\"");
  }
  else if(writePasswordVar == "1234" || writePasswordVar == "0000"){
    SendDataNextion("errorMessage.txt=", "\"Votre code n'est pas assez fort.\"");
  }
  else{
    SendDataNextion("errorMessage.txt=", "\"\"");
  }
}

// Confirm password
void confirmPassword(){
  if(writePasswordVar == password){
    SendDataNextion("page", "6");
    // Tortue : C'est ici pour mettres les moteurs
  }
  else{
    SendDataNextion("errorMessage.txt=", "\"Votre code est incorrect.\"");
  }
}

//Function AddPhone
//Type : wireless, cable
void addPhone(String _type){
  type = _type;
  password = "";
  SendDataNextion("page", "4");
  SendDataNextion("passwordTxt.txt=", "\"" + password + "\"");
  SendDataNextion("title.txt=", "\" Ajouter un code \"");
  SendDataNextion("description.txt=", "\" Vous devrez retenir ce code pour récupérer votre smartphone. \"");
}

//Function RecoverPhone
void recoverPhone(){
}

void endProcess(){
  String password = "";
  SendDataNextion("page", "0");
  writePasswordVar = "";
}
