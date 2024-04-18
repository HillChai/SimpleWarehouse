#pragma once

#include <Wire.h>
#include <Arduino.h>

class slave{
public:
  static  String comdata;

  slave();
  void initialize(int add);
static void receiveEvent(int howmany);
};