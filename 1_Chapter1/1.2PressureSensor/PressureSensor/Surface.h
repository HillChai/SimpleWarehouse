#pragma once

#include "HX711.h"
#include <EEPROM.h>

class Surface : public HX711 {
union coeffience {
  unsigned long offboard;
  byte onboard[4];
};

public:
  unsigned long Surfacevalue;
  float Gapvalue;
  int range;

  Surface(){};
  Surface(int p1, int p2, int r);
  unsigned long Get_Surfacevalue();
  float Get_Gapvalue();
  void Set_Surfacevalue();
  void Set_Gapvalue();
  void Output_Surfacevalue();
  void Output_Gapvalue();
};