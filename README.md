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
