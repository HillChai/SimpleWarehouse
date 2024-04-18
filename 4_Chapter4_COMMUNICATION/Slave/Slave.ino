#include "Slave.h"

Slave slave(11);

void setup() {
  Serial.begin(9600);
  slave.init();
}

void loop() {
  slave.feedback();
  delay(500);
}
