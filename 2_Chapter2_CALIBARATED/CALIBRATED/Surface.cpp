#include "Surface.h"

Surface::Surface(){
    coeffience memory;
    for (int i=0; i<4; ++i)
      memory.value_in[i]=EEPROM.read(i);
    AD_Surface = memory.value_out;
    flag=0;
};

unsigned long Surface::Get_Surface(){
  if (flag) {
    unsigned long AD_Sum=0, AD_Read=0;
    for (int i=0; i<10; ++i){
      AD_Read = HX711_Read();
      Serial.println(AD_Read);
      AD_Sum+=AD_Read;
    } 
    AD_Surface = AD_Sum/10;

    coeffience AD_Surface_out;
    AD_Surface_out.value_out = AD_Surface;

    for(int i=0; i<4; i++)    //判断是否与上次储存的AD_Surface相同
      if (!(EEPROM.read(i)==AD_Surface_out.value_in[i])) {
        Serial.println("OVERWRITE");
        for (int i=0; i<4; i++) 
          EEPROM.write(i, AD_Surface_out.value_in[i]);
        break;
      }
  flag = 0;
  } 
  return AD_Surface;
};

void Surface::setpin_SCKDT(int p1, int p2) {
  pin_SCK = p1;
  pin_DT = p2;
  pinMode(pin_DT, INPUT);	
  pinMode(pin_SCK, OUTPUT);	
  flag=1;
};

unsigned long Surface::HX711_Read() {
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