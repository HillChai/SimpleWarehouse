#include <SoftwareSerial.h>
#include <Arduino.h>

#define LF 0X0A
#define CR 0X0D
const int arrayMax =33;
const unsigned char MultiEPC[] = {0x0A, 0x55, 0x2C, 0x52, 0x31, 0x2C, 0x31, 0x2C, 0x37, 0x0D}; //同时读取多张卡的指令
const unsigned char WriteEPC[] = {0x0A, 0x57, 0x31, 0x2C,  //第一个0x31表示EPC区
                                  0x32, 0x2C,    //从第2个位置开始
                                  0x33, 0x2C,  //这里是写的三个字节, 最多八个地址,每个地址4字节
                                  0x30, 0x30, 0x3A, 0x3A, //物品种类
                                  0x30, 0x30, 0x31, 0x30, //单个物品质量
                                  0x30, 0x30, 0x30, 0x30, 0x0D};  //外壳质量

class RC505 {
private:
  SoftwareSerial WIFISerial = SoftwareSerial(6, 7);
public:
  char Type_Name[3];  
  long Single_Weight;
  long Shell_Weight;
  
  RC505();
  bool read(char *sub);
  void write();
};