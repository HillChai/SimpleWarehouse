#include "DataCollect.h"

DataCollect dc(4, 5, 20);

void setup() {
  Serial.begin(9600);
}

void loop() {
  dc.Output_data();
  delay(500);
}
