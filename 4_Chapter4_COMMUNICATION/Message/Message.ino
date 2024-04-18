#include "Message.h"

Message message;

char type[2] = {'0', '3'};   //pack
int address = 8;
int num = 321;
unsigned long totalmass=19;
// char data[17] = {'S','S','0','4','0','9','0','5','0','5','2','0','0','0','R','R'};   //unpack

void setup() {
  Serial.begin(9600);
  message.Set_Messagevalues(type, address, num, totalmass);      //pack
  message.pack();
  // message.Set_Data(data);  //unpack
  // message.unpack();
}

void loop() {
  message.Output_pack(); //pack
  // message.Output_unpack();  //unpack
  delay(500);
}
