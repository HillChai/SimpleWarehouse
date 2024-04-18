#pragma once 

#include <Arduino.h>
#include <string.h>

class Message {
private:
  char Data[17];
  char Type[4];
  int DeviceAddress, Amount;
  unsigned long TotalMass;
  int totalmass_str_len;

public:
  Message();
  
  void Set_Messagevalues(char *type, int device, int amount, unsigned long totalmass);
  void pack();
  void Output_pack();

  void Set_Data(char* message);
  void unpack();
  void Output_unpack();
};