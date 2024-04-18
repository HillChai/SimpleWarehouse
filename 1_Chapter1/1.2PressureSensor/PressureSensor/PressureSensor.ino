#include "PressureSensor.h"

PressureSensor ps(4,5,20);

void setup() {
  Serial.begin(9600);
  // ps.Set_Surfacevalue();	
}

void loop() {
  ps.Set_Weight();
  ps.Output_Weight();
  delay(500);
}
