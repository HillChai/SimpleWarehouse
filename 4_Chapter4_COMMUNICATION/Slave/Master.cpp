#include "Master.h"

Master::Master(int add){
  address=add;
};

void Master::init() {
  Wire.begin(address);
  Wire.onReceive(receiveEvent);
  memset(Data, '0', 16);
};

void Master::Set_Data(String message) {
  for (int i=0; i<message.length(); i++)
    Data[i] = message[i];
};

void Master::Send(int slave_add) {
  Wire.beginTransmission(slave_add);
  Wire.write(Data);
  Wire.endTransmission(slave_add);
  Serial.println("Sended");
};

bool Master::Gotitflag = 0;

void Master::receiveEvent(int howmany){
  String standard = "Gotit!";
  String buffer = "";
  while (Wire.available()) 
    buffer += (char) Wire.read();
  Serial.println(buffer);
  for (int i=0; i<6; i++)
    if (buffer[i] == standard[i])
      Gotitflag = 1;
};



