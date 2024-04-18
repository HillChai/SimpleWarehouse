#include "Oled.h"

void Oled::initialize() {
  display = Adafruit_SSD1306(128, 64, &Wire, -1);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
};

void Oled::show0(unsigned long val) {
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);

  Wire.beginTransmission(0x70);
  Wire.write(1<<0);
  Wire.endTransmission();
  display.clearDisplay(); // 清除屏幕

  //设置字体大小 设置字体颜色,白色可见
  display.setTextSize(2);
  display.setTextColor(WHITE);

  //设置光标位置 
  display.setCursor(20, 10);
  display.print(val);
  display.display();  
};

void Oled::show1(unsigned long val) {
  digitalWrite(A0,HIGH);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);

  Wire.beginTransmission(0x71);
  Wire.write(1<<1);
  Wire.endTransmission();
  display.clearDisplay(); // 清除屏幕

  //设置字体大小 设置字体颜色,白色可见
  display.setTextSize(2);
  display.setTextColor(WHITE);

  //设置光标位置 
  display.setCursor(20, 10);
  display.print(val);
  display.display();  
};

void Oled::show2(unsigned long val) {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A0,LOW);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,LOW);

  Wire.beginTransmission(0x72);
  Wire.write(1<<2);
  Wire.endTransmission();
  display.clearDisplay(); // 清除屏幕

  //设置字体大小 设置字体颜色,白色可见
  display.setTextSize(2);
  display.setTextColor(WHITE);

  //设置光标位置 
  display.setCursor(20, 10);
  display.print(val);
  display.display();  
};

void Oled::show3(unsigned long val) {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,LOW);

  Wire.beginTransmission(0x73);
  Wire.write(1<<3);
  Wire.endTransmission();
  display.clearDisplay(); // 清除屏幕

  //设置字体大小 设置字体颜色,白色可见
  display.setTextSize(2);
  display.setTextColor(WHITE);

  //设置光标位置 
  display.setCursor(20, 10);
  display.print(val);
  display.display();  
};

void Oled::show4(unsigned long val) {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,HIGH);

  Wire.beginTransmission(0x74);
  Wire.write(1<<4);
  Wire.endTransmission();
  display.clearDisplay(); // 清除屏幕

  //设置字体大小 设置字体颜色,白色可见
  display.setTextSize(2);
  display.setTextColor(WHITE);

  //设置光标位置 
  display.setCursor(20, 10);
  display.print(val);
  display.display();  
};

void Oled::show5(unsigned long val) {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A0,HIGH);
  digitalWrite(A1,LOW);
  digitalWrite(A2,HIGH);

  Wire.beginTransmission(0x75);
  Wire.write(1<<5);
  Wire.endTransmission();
  display.clearDisplay(); // 清除屏幕

  //设置字体大小 设置字体颜色,白色可见
  display.setTextSize(2);
  display.setTextColor(WHITE);

  //设置光标位置 
  display.setCursor(20, 10);
  display.print(val);
  display.display();  
};

void Oled::show6(unsigned long val) {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A0,LOW);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);

  Wire.beginTransmission(0x76);
  Wire.write(1<<6);
  Wire.endTransmission();
  display.clearDisplay(); // 清除屏幕

  //设置字体大小 设置字体颜色,白色可见
  display.setTextSize(2);
  display.setTextColor(WHITE);

  //设置光标位置 
  display.setCursor(20, 10);
  display.print(val);
  display.display();  
};

void Oled::show7(unsigned long val) {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);

  Wire.beginTransmission(0x77);
  Wire.write(1<<7);
  Wire.endTransmission();
  display.clearDisplay(); // 清除屏幕

  //设置字体大小 设置字体颜色,白色可见
  display.setTextSize(2);
  display.setTextColor(WHITE);

  //设置光标位置 
  display.setCursor(20, 10);
  display.print(val);
  display.display();  
};

