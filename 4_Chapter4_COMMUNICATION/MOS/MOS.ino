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
  pinMode(3,INPUT);
}

void loop() {
  if (s.comdata!=""){
    tf.unpack(s.comdata);
    s.comdata="";
    digitalWrite(3, HIGH);  
    oled.show(tf.Type_Name, tf.Number, tf.DEVICE_ADDRESS);
    digitalWrite(3,LOW);
  }
  delay(1000);
}

