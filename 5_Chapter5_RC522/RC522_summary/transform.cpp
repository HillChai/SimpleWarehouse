#include "transform.h"
#include <Arduino.h>

transform::transform(){};

void transform::initialize(char *Type, int DEVICE, int num, unsigned long W){
  for(int i=0; i<2; i++) Type_Name[i] = Type[i];
  DEVICE_ADDRESS = DEVICE;
  Number = num;
  Weight = W;
};

void transform::pack() {
  Transmission_Information[0] = Type_Name[0];
  Transmission_Information[1] = Type_Name[1];

  if (DEVICE_ADDRESS < 10)
  {
      Transmission_Information[2] = 0 + 48;
      Transmission_Information[3] = DEVICE_ADDRESS + 48;
  }
  else
  {
      Transmission_Information[2] = DEVICE_ADDRESS / 10 + 48;
      Transmission_Information[3] = DEVICE_ADDRESS % 10 + 48;
  }

  if (Number < 0)
  {
      Number = -Number;
      Transmission_Information[4] = 48;
      Transmission_Information[5] = 48;
      Transmission_Information[6] = 48;
      Transmission_Information[7] = 48;
  }
  else
  {
      byte k = 4;
      while (Number / 10 > 0)
      {
          Transmission_Information[k] = (Number % 10) + 48;
          Number = Number / 10;
          ++k;
      }
      for (int i = k; i < 8; ++i)
      {
          Transmission_Information[i] = 48;
      }
      Transmission_Information[k] = Number + 48;
      byte num = 4;
      for (int j = num; j < (8 -3)/2+4; ++j)
      {
          char m = Transmission_Information[j];
          Transmission_Information[j] = Transmission_Information[8-1 - j + num];
          Transmission_Information[8-1 - j + num] = m;
      }
  }
  
  if (Weight < 0)
  {
      Weight = -Weight;
      Transmission_Information[8] = 48;
      Transmission_Information[9] = 48;
      Transmission_Information[10] = 48;
      Transmission_Information[11] = 48;
      Transmission_Information[12] = 48;
      Transmission_Information[13] = 48;
  }
  else
  {
      byte k = 8;
      while (Weight / 10 > 0)
      {
          Transmission_Information[k] = (Weight % 10) + 48;
          Weight = Weight / 10;
          ++k;
      }
      for (int i = k; i < 14; ++i)
      {
          Transmission_Information[i] = 48;
      }
      Transmission_Information[k] = Weight + 48;
      byte num = 8;
      for (int j = num; j < (14 - 8) / 2 + 8; ++j)
      {
          char m = Transmission_Information[j];
          Transmission_Information[j] = Transmission_Information[14-1 - j + num];
          Transmission_Information[14-1 - j + num] = m;
      }
  }
  Transmission_Information[14] = '\0';  
};

void transform::show() {
  Serial.println(Transmission_Information);
}