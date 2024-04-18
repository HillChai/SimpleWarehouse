#pragma once 

class transform {
private:
  char Type_Name[3];
  int DEVICE_ADDRESS;
  long Number;
  unsigned long Weight;
public:
  char Transmission_Information[15];

  transform();
  void initialize(char *Type, int DEVICE, int num, unsigned long W);
  void pack();
  void show();
};