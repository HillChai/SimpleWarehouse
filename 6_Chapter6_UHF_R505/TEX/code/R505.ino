#include <Vector.h>
#include <SoftwareSerial.h>
#include <Array.h>
//收发指令的开头和结尾
#define LF 0X0A
#define CR 0X0D
//接收到的完整消息的字节长度
const int arrayMax =36；
//定义引脚6，7开通软串口
SoftwareSerial WIFISerial(6, 7); // RX, TX
//存储一次读取的多张卡字节数组消息的数组
Vector<Array<char,arrayMax>> message;
//存储单条消息的字节数组
Array<char,arrayMax> subMessage;
//处理消息函数
void getMessage(char mark);

//读取单张卡起始地址为1读取长度为7*4的指令
unsigned char Read_1EPC[] = {0X0A,0X52,0X31,0X2C,0X31,0X2C,0X37,0X0D};
//同时读取多张卡的指令
unsigned char MulitEPC[] = {0X0A,0X55,0X2C,0X52,0X31,0X2C,0X31,0X2C,0X37,0X0D};
//选择最后四个字节为5555的卡的指令
unsigned char SelectCard[] = {0X0A,0X54,0X31,0X2C,0X37,0X30,0X2C,0X31,0X30,0X2C,0X35,0X35,0X35,0X35,0X0D};
//向卡内从起始地址为2长度为4*1的地方写入8888
unsigned char WriteEPC[] = {0X0A,0X57,0X31,0X2C,0X32,0X2C,0X31,0X2C,0X39,0X39,0X39,0X39,0X0D};
//I2C通信每次智能读取一个字节，记录读取的内容
unsigned char incomedate = 0;

// Vector<Array<char,arrayMax>> getMessage(char mark);
int lock = 0;

void setup() {

  //设置串口波特率38400
  Serial.begin(38400); 
  //软串口波特率为38400
  WIFISerial.begin(38400); 
}



void loop() {
  //适当的延迟使得软串口可以将接收到的信息均处理完
  delay(100);
  // WIFISerial.write(Read_1EPC_1_7,sizeof(Read_1EPC_1_7));
  // WIFISerial.write(SelectCard,sizeof(SelectCard));
  // WIFISerial.write(WriteEPC,sizeof(WriteEPC));

  WIFISerial.write(MulitEPC,sizeof(MulitEPC));
  //返回消息的第二个字节位输入指令的第二个字节，需要作为参数输入
  getMessage(MulitEPC[1]);
   Serial.println(message.size());
   for(Array<char,arrayMax> subMessage : message)
   {
     for(int i = 0;i<arrayMax;i++){
      Serial.print(subMessage[i]); 
       Serial.print(' ');          
    }
     Serial.println();
    }
}


void getMessage(char mark)
{


  int start1 = 0;
  int start2 = 0;
  int end1 = 0;
  int end2 = 0;
  int count = 0;
  while(WIFISerial.available() > 0)
  {  
    //获取串口接收到的数据
    incomedate = WIFISerial.read();
    // Serial.print(incomedate);
    // Serial.print(' ');
    //当读取到第一个字节为LF，第二个字节为输入指令的第二个字节时卡的内容开始读取
    if(start1 == 0 && incomedate == LF){
      start1 = 1;
      continue;
    }
    if(start1 == 1 && start2 == 0 && incomedate == mark){
      start2 = 1;
      continue;
    }
    //结尾标志CR和LF
    if(start1 == 1 && start2 == 1 && end1 == 0 && incomedate != CR){
      subMessage.push_back(incomedate);    
      count++; 
      continue;
    }else if(start1 == 1 && start2 == 1 && end1 == 0 && incomedate == CR){
      end1 = 1;
      continue;
    }
    if(incomedate != LF){
      end1 = 0;
      subMessage.push_back(CR);
      subMessage.push_back(incomedate);
      count++;
      count++;
    }else{
	//判断是否读取到完整卡的信息
      if(count == arrayMax){
        message.push_back(subMessage);
      }
	//初始化各种标志
      subMessage.clear();
      start1 = 0;
      start2 = 0;
      end1 = 0;
      end2 = 0;
      count = 0;
    }
  }
}
