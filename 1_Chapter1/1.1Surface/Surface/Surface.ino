#include "Surface.h"

Surface s(4,5,20);

void setup() {
  Serial.begin(9600);
  s.Set_Gapvalue();
  s.Output_Gapvalue();
}

void loop() {
  s.Set_Surfacevalue();
  s.Output_Surfacevalue();
  delay(500);
}
