#pragma once

#include <Arduino.h>
#include <EEPROM.h>

class Surface{
union coeffience {
  unsigned long value_out;
  byte value_in[4];
};

private:
  int pin_SCK, pin_DT, range;   
  bool flag;
  unsigned long AD_Surface;

  unsigned long HX711_Read();

public:

  Surface();
  void setpin_SCKDT(int p1, int p2);
  unsigned long Get_Surface();
};