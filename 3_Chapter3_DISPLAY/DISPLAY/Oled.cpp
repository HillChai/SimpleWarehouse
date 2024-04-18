#include "Oled.h"

Oled::Oled() {
  display = Adafruit_SSD1306(128, 64, &Wire, -1);
};

void Oled::init(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
};

void Oled::Set_Oledvalue(String d1, String d2, String d3, String d4){
  data1 = d1;
  data2 = d2;
  data3 = d3;
  data4 = d4;
};

void Oled::Output_Oledvalue(){
  display.clearDisplay(); // 清除屏幕

  //设置字体大小 设置字体颜色,白色可见
  display.setTextSize(2);
  display.setTextColor(WHITE);

  //设置光标位置 
  display.setCursor(5, 5);
  display.print(data1);
  display.setCursor(69, 5);
  display.print(data2);
  display.setCursor(5, 37);
  display.print(data3);
  display.setCursor(69, 37);
  display.print(data4);

  display.display(); 
};


