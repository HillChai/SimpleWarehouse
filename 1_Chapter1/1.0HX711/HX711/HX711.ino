#include "HX711.h"

HX711 hx711(4, 5);

void setup() {
  Serial.begin(9600);
}

void loop() {
  hx711.Set_HX711value();
  hx711.Output_HX711();
  delay(500);
}
