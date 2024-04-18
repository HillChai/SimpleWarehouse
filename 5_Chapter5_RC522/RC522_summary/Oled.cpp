#include "Oled.h"

void Oled::initialize() {
  display = Adafruit_SSD1306(128, 64, &Wire, -1);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
};

void Oled::show(unsigned long val) {
  display.clearDisplay(); // 清除屏幕

  //设置字体大小 设置字体颜色,白色可见
  display.setTextSize(2);
  display.setTextColor(WHITE);

  //设置光标位置 
  display.setCursor(20, 10);
  display.print(val);
  display.display();  
};

void Oled::showIIC(char *type, int num) {
  display.clearDisplay(); // 清除屏幕

  //设置字体大小 设置字体颜色,白色可见
  display.setTextSize(4);
  display.setTextColor(WHITE);

  //设置光标位置 
  display.setCursor(5, 10);
  display.print(type[0]);
  display.print(type[1]);
  display.print(":");
  display.print(num);
  display.display(); 
}

