#include "RC505.h"

RC505::RC505(){
  WIFISerial.begin(38400);  //软串口波特率为38400
};

void RC505::write(){
  WIFISerial.write(WriteEPC, sizeof(WriteEPC));
};

bool RC505::read(char *sub){
  WIFISerial.write(MultiEPC, sizeof(MultiEPC));
  
  int start1 = 0;
  unsigned char buffer = 0;
  int i=0;

  while(WIFISerial.available() > 0) { 
    buffer = (char)WIFISerial.read();   //获取串口接收到的数据

    if(start1 == 0 && buffer == LF){  //当读取到第一个字节为LF
      start1 = 1;
      continue;
    }

    if(start1 == 1 && buffer != CR){  //结尾标志CR和LF
      // Serial.print((char)buffer);
      sub[i]=(char)buffer; 
      i++;
      if(i==arrayMax) {
        // Serial.println(' ');
        break;
      }   
      continue;
    }

  }

  int w=0;
  for (int i=7;i<9;i++) Type_Name[i-7]=sub[i];
  for (int i=11;i<13;i++) {
    w += (sub[i]-48)*pow(10,12-i);
    // Serial.println(w);
  }
  Single_Weight=w;
  return 1;
};