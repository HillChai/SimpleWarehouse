#include "Oled.h"

Oled oled;

void setup() {
  Serial.begin(9600);
  oled.init();
}

void loop() {
  oled.Set_Oledvalue("CC", "100", "10", "1000");
  oled.Output_Oledvalue();
}
