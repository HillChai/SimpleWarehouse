#include "Surface.h"

Surface::Surface(int p1, int p2, int r) : HX711(p1, p2){
  coeffience memory;
  for (int i=0; i<4; ++i)
    memory.onboard[i]=EEPROM.read(i);
  if (memory.offboard!=0)
    Surfacevalue = memory.offboard;

  range = r;
};

unsigned long Surface::Get_Surfacevalue() {
  unsigned long AD_Sum=0, AD_Read=0;
  for (int i=0; i<10; ++i){
    AD_Read = Get_HX711value();
    AD_Sum+=AD_Read;
  }
  unsigned long value = AD_Sum/(10*Gapvalue);

  return value;
};

float Surface::Get_Gapvalue() {
  return 128 * 16.777215 / range;
};

void Surface::Set_Surfacevalue() {
  Surfacevalue = Get_Surfacevalue();
  coeffience buffer_Surface;
  buffer_Surface.offboard = Surfacevalue;

  for(int i=1; i<4; i++)    //判断是否与上次储存的AD_Surface相同
    if (!(EEPROM.read(i)==buffer_Surface.onboard[i])) {
      Serial.println("OVERWRITE");
      EEPROM.write(i, buffer_Surface.onboard[i]);
    }  
};

void Surface::Set_Gapvalue() {
  Gapvalue = Get_Gapvalue();
};

void Surface::Output_Surfacevalue() {
  Serial.print("Surfacevalue:");
  Serial.println(Surfacevalue);
}

void Surface::Output_Gapvalue() {
  Serial.print("Gapvalue:");
  Serial.println(Gapvalue);  
};

