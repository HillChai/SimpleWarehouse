#pragma once

#include "PressureSensor.h"

class DataCollect{
private:
  PressureSensor ps;

public:
  DataCollect() {};
  DataCollect(int p1, int p2, int r);
  void Output_data();
};