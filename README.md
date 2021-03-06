# Station de recharge pour smartphone📱
La station de recharge pour smartphone est un projet de terminale (STI2D). Il consiste à pouvoir accueillir des smartphones (de tous genres) pour une recharge simple, rapide et sécurisé. Le projet doit être fondé sur "une autonomie énergétique".

## Communication Arduino - Nextion
### Envoyer des commandes 
Pour envoyer des commandes à lécran Nextion, il faut créer un SerialPort. Ici ils sont sur les pins : ```10``` et ```11```.
``` c++
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
```
Les commandes doivent être sous la forme : 
```c++
locAvailable.val="1";
```	
Elles sont envoyées sur les ports Rx Tx avec des ```print()```
```c++ 
void SendDataNextion(String action, String value){
    nextionSerial.print(action); // Commande à envoyer 
    nextionSerial.print(value); // Valeur à envoyer
    nextionSerial.write(0xff); // Caractère de fin de transmission
    nextionSerial.write(0xff); // Caractère de fin de transmission
    nextionSerial.write(0xff); // Caractère de fin de transmission
}
``` 
### Envoyer des commandes depuis le Serial (IDE Arduino)
Vous pouvez envoyer des commandes depuis le Serial de l'IDE Arduino.<br/>
Il suffit d'aller dans le Serial Monitor de l'IDE Arduino et de taper les commandes suivantes :<br/>
***(La commande et la valeur doit être séparé par un espace)***<br/>

```variable.val=``` ```2``` : Modifier la valeur d'une variable (Ici, met la valeur de variable à 2)<br/>
```page``` ```14``` ou ```page``` ```wait```  : Modifier la valeur d'un bouton (Ici, va à la page wait ou 14)<br/>

### Récupérer des données
Pour récupérer des données, il faut créer une fonction qui va recevoir les données. La fonction attend de recvoir un signal du port ```portSecondaire``` et va les stocker dans un tableau.
```c++
void ReceiveDataNextion(){
  delay(100);
  if  (nextionSerial.available()){
    for (int i = 0; i < 7; i++) {
      messageReceived[i] = nextionSerial.read();
    }
  }
}
```
### Reception des données
Les données reçu par le port ```portSecondaire``` sont stockées sous la forme : 
```c++
101,0,1,1,255,255,255
```
Le ```101``` correspond au type d'élément.<br/>
Le ```0``` correspond à l'ID de la page qui possède le bouton.<br/>
Le ```1``` correspond à l'ID du bouton qui a été cliqué.<br/>
Le ```1``` indique si "Send Component ID" à été cliqué.<br/>
Les ```255``` correspond à la fin de l'event.<br/>
### Traitement des données reçu
Le traitements des données reçu est le suivant :<br/>
Les boutons sont d'abbord stockés comme dans l'exemple ci-dessous :<br/>
```c++
struct Button {
  byte pageId;
  byte buttonId;
  void (*button_func) (void);
};

Button buttons[] = {
  { 0, 3, []() { SendDataNextion("page", "2"); } }, //Btn (Recharger son smartphone)
  { 2, 2, []() { SendDataNextion("page", "2"); } }, //Btn (Ajouter son smartphone)
};
```

Le premier élément correspond à *l'ID de la page*, le second à *l'ID du bouton* et le troisième à la *fonction* qui sera exécuté lorsque le bouton est cliqué.
<br/>
<br/>
Un programme cherche donc une corresposndance avec l'ID page et l'ID bouton dans la liste des boutons ci-dessus.
```c++
for (size_t i = 0; i < bsize; i++) {
  if (buttons[i].pageId == pageId && buttons[i].buttonId == buttonId) {
    buttons[i].button_func();
  }
```

## Code et identifiant
### Code
Une page Code unique à été créé pour choisir, confirmer et entrer un mot de passe.
<br/>
Une fonction à été créé pour recevoir l'action demandé par l'écran.
```c++
void writePassword(String actionOrNumber){
  // Code 
}
```
```String actionOrNumber``` correspond à l'action demandé par l'écran.	
<br/>
Le programme applique ensuite l'action demandé par l'écran.
<br/>
<br/>
D'autres programmes se chargent de vérifier si le mot de passe est correct et si il peut être validé.
```c++	
void validatePassword(){
  if(writePasswordVar.length() < 4){
    // Code
  }
  else if(writePasswordVar == "1234" || writePasswordVar == "0000"){
    // Code
  }
  else{
    // Envoyer le mot de passe.
  }
}
```
### Identifiant
La page identifiant fonctionne du même mécanisme que la page code.
<br/>
L'identifiant est donné lorsque l'utilisateur ajoute un smartphone et il doit le saisir pour pouvoir le retirer.
```c++
void confirmId(){
  if(id.length() == 1 && id == idDansLaListe){ //Tortue : Ici pour tester si ID ets dans la liste
    SendDataNextion("page", "4");
  }
  else{
    SendDataNextion("errorMessage.txt=", "\"l'Id est incorrect.\"");
  }
}
```
La page suivante demande le code correspondant à l'identifiant. (Même page que pour ajouter un code)

## Pages d'actions avec la station
Une fonction est prévue pour afficher les pages du processus en fonction de la situation. Les fonctions s'occupants de la station n'ont qu'à appeler ces fonctions dès que leur processus est terminé.
<br/>
<br/>
Liste des processus :
<br/>
- Le processus ```0``` signifie que l'utilisateur est sur la page d'accueil.
- Le processus ```1``` signifie que l'utilisateur est daans le processus d'ajout d'un smartphone.
- Le processus ```2``` signifie que l'utilisateur est dans le processus de récupération d'un smartphone.

Liste des actions :
<br/>
- L'action ```1``` correspond à l'ouverture de la porte.
- L'action ```2``` correspond à la page demandant à l'utilisateur de récupérer ou placer son smartphone.
- L'action ```3``` correspond à la page qui affiche le message de remerciement.

```c++
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
```
