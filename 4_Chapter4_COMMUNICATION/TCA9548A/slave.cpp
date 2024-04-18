#include "slave.h"

slave::slave(){};

void slave::initialize(int add){
  Wire.begin(add);
  Wire.onReceive(receiveEvent);
};

void slave::receiveEvent(int howmany){
  String buffer="";
  while(Wire.available()) {
    buffer += (char) Wire.read();
  }
  comdata = "";
  for (char i:buffer) comdata+=i;
  Serial.print("comdata:");
  Serial.println(comdata);
};



