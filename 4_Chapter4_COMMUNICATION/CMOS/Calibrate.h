#pragma once

#include <Arduino.h>
#include <EEPROM.h>

class Calibrate {
union coeffience {
  unsigned long value_out;
  byte value_in[4];
};

private:
  int pin_SCK, pin_DT, range; 
  float GapValue;
  unsigned long k, b;
  unsigned long x[6];

public:
  Calibrate();

  void Get_x_array(unsigned long ADS);
  void Get_kb();
  unsigned long Output_CalibratedWeight(unsigned long weight);
  void kb_Initialize();

  void setpin_SCKDT(int p1, int p2);
  void set_range(int r);
  unsigned long Output_Weight(unsigned long ADS);
  unsigned long HX711_Read();
};