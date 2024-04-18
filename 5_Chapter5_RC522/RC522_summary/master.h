#pragma once

#include <Wire.h>
#include <Arduino.h>

class master {
public:
  int address;
  master();
  void initialize(int add);
  void send(int add, char *data);
};