/* ---------- Define pins ----------- */
  // Ecran
  #define ScreenRx 0
  #define ScreenTx 0
  /* ---------- End define pins ----------- */
  
  #include "motors.h"
  #include "management.h"
  #include "screen.h"
  #include "data.h"
  
  /******************************************\
   *          How program work
   * blablabla
   * blablabla
   * blabla
   * bla
   * blamanredra
   * blalalamabla
  \******************************************/
  
  /******************************************\
   *          Compiled infos
   * Bytes :      7378  / 32256  (22%)
   * Variables :  564   / 2048   (27%)
  \******************************************/
  
  #define DEBUG_MODE 1
  #define FINAL_PRINT 1
  
  void setup() {
  #if DEBUG_MODE == 1
    Serial.begin(9600);
    InitMotors();
    pinMode(2, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
  
    for (int i = 0; i < 10; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(50);
      digitalWrite(LED_BUILTIN, LOW);
      delay(50);
    }
    
    //InitScreen();  
  #elif
    // Code du projet final
  
  #if FINAL_PRINT == 1
    Serial.begin(9600);
    Serial.println("Starting");
  #endif
  
    // Inits
    InitData();
    InitMotors();
    InitManagement();
    InitScreen();
  #endif
  }
  
  int tp = 0;
  void loop() {
    ManageMotors();  // Manage
  
    // SI BOUTON INCREMENTE POS
    if (digitalRead(2) == HIGH) {
      digitalWrite(5, HIGH);
      tp = (tp + 1) % 8;
      SetAimedPos(tp);
      digitalWrite(LED_BUILTIN, tp == 0 ? HIGH : LOW);
      delay(200);
    }else{
      digitalWrite(5, LOW);
      
    }
    
    //SendDataNextion("locAvailable.val=", "5");
    //ReceiveDataNextion();
    //sendCommandFromSerial();
    delay(10);
  }
