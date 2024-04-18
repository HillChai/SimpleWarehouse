#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Oled {
private:
  String data1, data2, data3, data4;
  Adafruit_SSD1306 display;
public:
  Oled();
  void init();
  void Set_Oledvalue(String d1, String d2, String d3, String d4);
  void Output_Oledvalue();
};