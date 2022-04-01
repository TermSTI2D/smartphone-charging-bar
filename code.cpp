
struct Phone {
  byte id : 3;
  bool isEmpty : 1;
  char password[5];
};

struct AddPhoneInfos {
  bool hasSpace;
  byte id;
};

Phone phones[8] = {
  {0, true, "0000"},
  {1, true, "0000"},
  {2, true, "0000"},
  {3, true, "0000"},
  {4, true, "0000"},
  {5, true, "0000"},
  {6, true, "0000"},
  {7, true, "0000"},
};


AddPhoneInfos * GetAddPhoneInfos(bool wireless = false) {
  AddPhoneInfos* infos = new AddPhoneInfos { false, 255 };

  int _start = wireless ? 0 : 4;
  int _end = wireless ? 4 : 8;

  for (; _start < _end; _start++) {
    if (phones[_start].isEmpty)  {
      infos->hasSpace = true;
      infos->id = _start;
      break;
    }
  }

  return infos;
}

void AddPhone(AddPhoneInfos * infos, char password[5]) {
  if (infos->id == 255) return;
  Phone * p = &phones[infos->id];
  
  p->isEmpty = false;
  strcpy(p->password, password);
}


void setup() {
  Serial.begin(9600);
  Serial.println("    - Start");

  AddPhoneInfos * infos = GetAddPhoneInfos(true);

  char pass[5] = "1654";
  AddPhone(infos, pass);
  
  infos = GetAddPhoneInfos(false);
  char pass2[5] = "6547";
  AddPhone(infos, pass2);

  Serial.println(phones[0].isEmpty);
  Serial.println(phones[0].password);
  Serial.println(phones[1].isEmpty);
  Serial.println(phones[1].password);
  Serial.println(phones[4].isEmpty);
  Serial.println(phones[4].password);

  return;

  Serial.println( infos->id );
}

void loop() {}
