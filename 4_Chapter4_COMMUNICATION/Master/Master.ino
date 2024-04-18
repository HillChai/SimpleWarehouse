#include "Master.h"

Master master(8);

void setup() {
  Serial.begin(9600);
  master.init();
  master.Set_Data("SS0812345RR");
}

void loop() {
  while (!master.Gotitflag) {
    master.Send(11);
    delay(5000);
  }
  Serial.println("endsending");
  delay(500);
}
