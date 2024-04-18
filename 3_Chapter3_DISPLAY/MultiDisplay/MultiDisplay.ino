#include "Oled.h"
#include <Arduino.h>

Oled oled;

void setup() {
  Serial.begin(9600);
  
  oled.initialize();

  oled.show0(33);
  oled.show1(55);

}

void loop() {
}
