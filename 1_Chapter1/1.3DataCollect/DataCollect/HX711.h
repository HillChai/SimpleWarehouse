#pragma once 

#include <Arduino.h>

class HX711{
private:
  unsigned long HX711value;

public:
  int pin_SCK, pin_DT;   

  HX711(){};
  HX711(int p1, int p2);
  unsigned long Get_HX711value();
  void Set_HX711value();
  void Output_HX711value();
};