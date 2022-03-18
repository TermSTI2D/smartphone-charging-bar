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
### Traitement des données
Les données reçu par le port ```portSecondaire``` sont stockées sous la forme : 
```c++
101,0,1,1,255,255,255
```
Le ```101``` correspond au type d'élément.<br/>
Le ```0``` correspond à l'ID de la page qui possède le bouton.<br/>
Le ```1``` correspond à l'ID du bouton qui a été cliqué.<br/>
Le ```1``` indique si "Send Component ID" à été cliqué.<br/>
Les ```255``` correspond à la fin de l'event.<br/>
