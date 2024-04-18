#pragma once

#include <MFRC522.h>
#include <SPI.h>
#include <Arduino.h>

class RC522{
private:
  int RST_PIN, SS_PIN;
  MFRC522 mfrc522;                                           

public:
  char Type_Name[3];  
  long Single_Weight;
  long Shell_Weight;

  RC522();
  void initialize(int p1, int p2);
  byte read();
  bool write();
};


