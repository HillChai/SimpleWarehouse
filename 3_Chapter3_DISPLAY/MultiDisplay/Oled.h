#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Oled {
private:
  Adafruit_SSD1306 display;
public:
  void initialize();
  void show0(unsigned long val);
  void show1(unsigned long val);
  void show2(unsigned long val);
  void show3(unsigned long val);
  void show4(unsigned long val);
  void show5(unsigned long val);
  void show6(unsigned long val);
  void show7(unsigned long val);
};