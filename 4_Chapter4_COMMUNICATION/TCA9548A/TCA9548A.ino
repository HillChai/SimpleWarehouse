#include "Oled.h"
#include "slave.h"
#include "transform.h"

String slave::comdata="";

Oled oled;
slave s;
transform tf;

void setup() {
  Serial.begin(9600);
  s.initialize(8);
  oled.initialize();
  // pinMode(7,INPUT);
  // digitalWrite(7, LOW);
}

void loop() {
  tf.unpack(s.comdata);
  oled.showIIC(tf.Type_Name, tf.Number, tf.DEVICE_ADDRESS);
  // char s[2]={'B','B'};
  // oled.showIIC(s, 11, 9);
  delay(1000);
}

