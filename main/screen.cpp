#include <SoftwareSerial.h>
#include "screen.h"

// Variables
int messageReceived[7] = {};
String commandFromSerial = ""; 
String password = "";
String id ="";
byte process = 0; //0 = none, 1 = add, 2 = recvoer
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
  { 5, 2, []() { showLastPages(1); } }, //Btn (Ok ! page ID)
  { 8, 1, []() { endProcess(); } }, //Btn (Retour à l'acceuil)
  { 0, 4, []() { SendDataNextion("page", "9"); } }, //Btn Récupérer smartphone
  { 9, 2, []() { recoverPhone(); } }, //Btn Récupérer smartphone
  // WriteId
  { 10, 1, []() { writeId("1"); } }, //Btn "1"
  { 10, 2, []() { writeId("2"); } }, //Btn "2"
  { 10, 3, []() { writeId("3"); } }, //Btn "3"
  { 10, 4, []() { writeId("4"); } }, //Btn "4"
  { 10, 5, []() { writeId("5"); } }, //Btn "5"
  { 10, 6, []() { writeId("6"); } }, //Btn "6"
  { 10, 7, []() { writeId("7"); } }, //Btn "7"
  { 10, 8, []() { writeId("8"); } }, //Btn "8"
  { 10, 10, []() { writeId("erase"); } }, //Btn "erase"
  { 10, 9, []() { confirmId(); } }, //Btn "ok"
  { 14, 1, []() { endProcess(); } }, //Btn (Retour à l'acceuil)
};

size_t bsize = sizeof(buttons) / sizeof(Button);



// char buttons[buttonsLine][buttonsColumn] = { //[Lignes][Colones]
//   {'0','3','SendDataNextion(page, 2)'} //Page ID, Button ID, Function
// };

SoftwareSerial  nextionSerial(screenRx, screenTx); // RX, TX

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
    }
    else if(writePasswordVar.length() < 4){
      writePasswordVar = writePasswordVar + actionOrNumber;
    }
  SendDataNextion("passwordTxt.txt=", "\"" + writePasswordVar + "\"");
}

// Write Id
void writeId(String actionOrNumber){
    if(actionOrNumber == "erase"){
      int length=id.length();
      id.setCharAt(length-1,'\t');
      id.trim();
    }
    else if(id.length() < 1){
      id = id + actionOrNumber;
    }
  SendDataNextion("idTxt.txt=", "\"" + id + "\"");
}

// Validate password
void validatePassword(){
  if(writePasswordVar.length() < 4){
    SendDataNextion("errorMessage.txt=", "\"Votre code doit disposer de 4 chiffres.\"");
  }
  else if(writePasswordVar == "1234" && process == 1 || writePasswordVar == "0000" && process == 1){
    SendDataNextion("errorMessage.txt=", "\"Votre code n'est pas assez fort.\"");
  }
  else{
    SendDataNextion("errorMessage.txt=", "\"\"");
    if(process == 1){
      if(password == ""){
        password = writePasswordVar;
        writePasswordVar = "";
        SendDataNextion("passwordTxt.txt=", "\"" + writePasswordVar + "\"");
        SendDataNextion("title.txt=", "\" Confirmer le code \"");
        SendDataNextion("description.txt=", "\" Vous devez ressaisir votre code. \"");      
      }
      else{
        confirmPassword();
      }
    }
    else if(process == 2){
      if(writePasswordVar == writePasswordVar){ // Tortue : Ici pour vérifier si mot de passe correspond à ID
        recoveryProcess();
      }
      else{
        SendDataNextion("errorMessage.txt=", "\"Votre code n'est pas bon.\"");
      }  
    }
  }
}

// Confirm password
void confirmPassword(){
  if(writePasswordVar == password){
    //Give ID
    SendDataNextion("page", "5");
    SendDataNextion("id.val=", "2"); //Le 2 est à remplacer par une fonction d'ID
    // Tortue : C'est ici pour mettres le l'ID

    // C'est provisoir !! (donc à enlever après)
    delay(2000);
    showLastPages(1); // Page "Ouverture porte"
    delay(2000);
    showLastPages(2); // Page "vous pouvez placer votre smartphone"
    delay(2000);
    showLastPages(3); // Page "Remerciement"

  }
  else{
    SendDataNextion("errorMessage.txt=", "\"Votre code est incorrect.\"");
  }
}

// Confirm ID

void confirmId(){
  if(id.length() == 1 && id == id){ //Tortue : Ici pour tester si ID ets dans la liste
    SendDataNextion("page", "4");
    SendDataNextion("passwordTxt.txt=", "\"" + password + "\"");
    SendDataNextion("title.txt=", "\" Quel est votre code ? \"");
    SendDataNextion("description.txt=", "\" Votre mot de passe correspond a celui que vous avez entre au depot de votre smartphone. \"");

  }
  else{
    SendDataNextion("errorMessage.txt=", "\"l'Id est incorrect.\"");
  }
}

//Function AddPhone
//Type : wireless, cable
void addPhone(String _type){
  type = _type;
  password = "";
  process = 1;
  SendDataNextion("page", "4");
  SendDataNextion("passwordTxt.txt=", "\"" + password + "\"");
  SendDataNextion("title.txt=", "\" Ajouter un code \"");
  SendDataNextion("description.txt=", "\" Vous devrez retenir ce code pour recuperer votre smartphone. \"");
}

//Function RecoverPhone
void recoverPhone(){
  process = 2;
  id = "";
  password = "";
  SendDataNextion("page", "10");
}
// Function Recovery process

void recoveryProcess(){
  SendDataNextion("page", "12"); //Page "Votre téléphone arrive"
  delay(2000);
  showLastPages(1);
  delay(2000);
  showLastPages(2);
  delay(2000);
  showLastPages(3);
}

// Function 
//  1 = ouverturePorte, 2 = Rocov/Place, 3 = message 
void showLastPages(byte action){ 
  if(action == 1){
    SendDataNextion("page", "6");
  }
  else if(action == 2 && process == 1){
    SendDataNextion("page", "7");
  }
  else if(action == 2 && process == 2){
    SendDataNextion("page", "13");
  }
  else if(action == 3 && process == 1){
    SendDataNextion("page", "8");
  }
  else if(action == 3 && process == 2){
    SendDataNextion("page", "14");
  }
} 

void endProcess(){
  String password = "";
  SendDataNextion("page", "0");
  writePasswordVar = "";
  process = 0;
  id = "";
  password = "";
}
