#pragma once

#include <Wire.h>
#include <Arduino.h>
#include <string.h>

class Master {
public:
  int address;
  char Data[17];
static bool Gotitflag;

  Master(int add);
  void init();
  void Set_Data(String message);
  void Send(int slave_add);
  bool isData_receivedNull();
static void receiveEvent(int howmany);
};