#include "RC505.h"

RC505 rc505;
char MessageNow[arrayMax];

void setup() {
  //设置串口波特率38400
  Serial.begin(38400);
}
bool flag=1;
void loop() {
  if (flag) {
    rc505.write();
    flag=0;
    delay(500);
  }
  rc505.read(MessageNow);
  for (char c:MessageNow) Serial.print(c);
  Serial.println(' ');
  for (char c:rc505.Type_Name) Serial.print(c);
  Serial.println(rc505.Single_Weight);
  delay(3000);  
}