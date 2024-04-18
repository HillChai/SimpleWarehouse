#include "Slave.h"

String Slave::Data_received="";
int Slave::address_to_send = 99;

Slave::Slave(int add) : Master(add) {};

void Slave::slave_receiveEvent(int howmany){
  memset(&Data_received, 0, Data_received.length());
  bool addressflag = 1;
  while(Wire.available()) {
    Serial.println("connect");
    if (Data_received[0] != 'S' && Data_received[1] != 'S') {
      char start1 = (char) Wire.read();
      if (start1 == 'S') {
        char start2 = (char) Wire.read();
        if (start2 == 'S') {
          Data_received += 'S';
          Data_received += 'S';
        } 
      }
    }

    if (Data_received[0] == 'S' && Data_received[1] == 'S') {
      if (Data_received[Data_received.length()-2]=='R' && Data_received[Data_received.length()-1]=='R') {
        Wire.read();
        if (addressflag) {
          String address;
          for (int i=0; i<2; i++) address += Data_received[2+i];
          address_to_send = address.toInt();
          addressflag = 0;
        }
      } else {
        char end1 = (char) Wire.read();
        Data_received += end1;
        // Serial.println(Data_received);
      }
    }
  }
  Serial.println(address_to_send);
};

void Slave::init(){
  Wire.begin(address);
  Wire.onReceive(slave_receiveEvent);
  memset(Data, '0', 16);
}

void Slave::feedback() {
  if (address_to_send!=99) {
    Wire.beginTransmission(address_to_send);
    Wire.write("Gotit!");
    Wire.endTransmission(address_to_send);
    address_to_send = 99;
  }  
};



