#include "HX711.h"

HX711::HX711(int p1, int p2){
  pin_SCK = p1;
  pin_DT = p2;
  pinMode(pin_DT, INPUT);	
  pinMode(pin_SCK, OUTPUT);	
};

unsigned long HX711::Get_HX711value() {
  unsigned long AD_value=0;
	digitalWrite(pin_DT, HIGH);
	delayMicroseconds(1);
	digitalWrite(pin_SCK, LOW);
	delayMicroseconds(1);
  while(digitalRead(pin_DT));
   
  for(unsigned char i=0;i<24;++i) {
	  digitalWrite(pin_SCK, HIGH); 
		delayMicroseconds(1);
	  AD_value <<= 1; 
		digitalWrite(pin_SCK, LOW); 
		delayMicroseconds(1);
	  if(digitalRead(pin_DT)) ++AD_value; 
    // Serial.println(AD_value);
	} 
	// AD_value ^= 0x800000;

 	digitalWrite(pin_SCK, HIGH); 
	delayMicroseconds(1);
	digitalWrite(pin_SCK, LOW); 
	delayMicroseconds(1);

  // Serial.println(AD_value);
  return AD_value;
};

void HX711::Set_HX711value() {
  HX711value = Get_HX711value();
}

void HX711::Output_HX711() {
  Serial.print("HX711value:");
  Serial.println(HX711value);
}