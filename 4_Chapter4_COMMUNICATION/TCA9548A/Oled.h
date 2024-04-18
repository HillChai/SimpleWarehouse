#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Oled {
private:
  Adafruit_SSD1306 display;
public:
  void initialize();
  void showIIC(char *type, int num, int i);
};