#include "Message.h"

Message::Message() {
  memset(Data, '0', 16);
  Data[0] = 'S';
  Data[1] = 'S';
  Data[14] = 'R';
  Data[15] = 'R';
  Type[0] = '0';
  Type[1] = '0';
  DeviceAddress = 0;
  Amount = 0;
  TotalMass = 0;
}

void Message::Set_Messagevalues(char *type, int device, int amount, unsigned long totalmass) {
  Type[0] = type[0];  //物品种类
  Type[1] = type[1];

  DeviceAddress = device;
  Amount = amount;
  TotalMass = totalmass;
  if (totalmass<10) totalmass_str_len = 1;
  else if (totalmass<100) totalmass_str_len = 2;
  else if (totalmass<1000) totalmass_str_len = 3;
  else if (totalmass<10000) totalmass_str_len = 4;
};

void Message::pack() {
  String device_str = String(DeviceAddress);
  String amount_str = String(Amount);
  char totalmass_str[5];
  sprintf(totalmass_str, "%d", TotalMass);

  for (int i=0; i<2; i++) 
    Data[2+i] = Type[i];  //物品种类

  int device_str_len = device_str.length();
  if (device_str_len == 1) {         //发送方地址
    Data[5] = device_str[0];
  }
  else if (device_str_len == 2) {
    Data[4] = device_str[0];
    Data[5] = device_str[1];
  }

  int amount_str_len = amount_str.length();   //物品数量
  if (amount_str_len == 1) Data[9] = amount_str[0];
  else if (amount_str_len == 2) 
    for (int i=0; i<2; i++) Data[8+i] = amount_str[i];
  else if (amount_str_len == 3) 
    for (int i=0; i<3; i++) Data[7+i] = amount_str[i];
  else if (amount_str_len == 4) 
    for (int i=0; i<4; i++) Data[6+i] = amount_str[i];

  if (totalmass_str_len == 1)    //物品总质量
    Data[13] = totalmass_str[0];
  else if (totalmass_str_len == 2)
    for (int i=0; i<2; i++) Data[12+i] = totalmass_str[i];
  else if (totalmass_str_len == 3)
    for (int i=0; i<3; i++) Data[11+i] = totalmass_str[i];
  else if (totalmass_str_len == 4)
    for (int i=0; i<4; i++) Data[10+i] = totalmass_str[i];
};

void Message::Set_Data(char* message) {
  for (int i=2; i<14; i++) 
    Data[i]=message[i];
}

void Message::unpack() {
  String device_str, amount_str;
  char totalmass_str[5];
  
  for (int i=0; i<2; i++)
    Type[i] = Data[2+i];

  for (int i=0; i<2; i++)
    device_str += Data[4+i];
  DeviceAddress = device_str.toInt();

  for (int i=0; i<4; i++) 
    amount_str += Data[6+i];
  Amount = amount_str.toInt();

  String tm_str;
  for (int i=10; i<14; i++) 
    tm_str += Data[i];
  TotalMass = tm_str.toInt(); 
};

void Message::Output_pack() {
  Serial.print("Data:");
  Serial.println(Data);
};

void Message::Output_unpack() {
  Serial.print("Type:");
  Serial.println(Type);
  Serial.print("DeviceAddress:");
  Serial.println(DeviceAddress);
  Serial.print("Amount:");
  Serial.println(Amount);
  Serial.print("TotalMass:");
  Serial.println(TotalMass);
};


