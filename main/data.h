#ifndef DATA_H
#define DATA_H

#include <Arduino.h>

struct phone {
  bool isEmpty = false;
  String pass_hash = "";
};

phone *LoadPhones();

#endif
