#pragma once

#include "Surface.h"

class PressureSensor : public Surface {
public:
  unsigned long Weight;

  PressureSensor(){};
  PressureSensor(int p1, int p2, int r);
  unsigned long Get_Weight();
  void Set_Weight();
  void Output_Weight();
};