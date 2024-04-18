#include "PressureSensor.h"

PressureSensor::PressureSensor(int p1, int p2, int r) : Surface(p1, p2, r){
  Set_Gapvalue();
}

unsigned long PressureSensor::Get_Weight() {
  unsigned long difference = Get_HX711value()/Gapvalue - Surfacevalue;
  if (difference > 20000 || difference < 4) difference = 0;			
  return difference;
};

void PressureSensor::Set_Weight() {
  Weight = Get_Weight();
};

void PressureSensor::Output_Weight() {
  Serial.print("Weight:");
  Serial.println(Weight);
};
