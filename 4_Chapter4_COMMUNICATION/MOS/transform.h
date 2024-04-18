#pragma once 

#include <Arduino.h>

class transform {
private:
  unsigned long Weight;
public:
  char Transmission_Information[15];
  char Type_Name[3];
  long Number;
  int DEVICE_ADDRESS;

  transform();
  void pack(char *Type, int DEVICE, int num, unsigned long W);
  void unpack(String data);
  void show();
};