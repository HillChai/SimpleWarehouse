#include "RC522.h"

RC522::RC522(){};

void RC522::initialize(int p1, int p2){
  RST_PIN=p1;
  SS_PIN=p2;
  SPI.begin();
  mfrc522 = MFRC522(SS_PIN, RST_PIN);                                           
  mfrc522.PCD_Init();  
};

byte RC522::read(){
  // init the read state
  byte read_state = 0;
  //default key 
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; ++i) key.keyByte[i] = 0xFF;
  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;
  //-------------------------------------------
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return read_state;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return read_state ;
  }
  // read one card
  read_state = 1;
  Serial.println(F("**Card Detected:**"));
  //-------------------------------------------
  // mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card
  // mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex
  //-------------------------------------------

  byte buffer1[18];
  block = 1;
  len = 18;
  //------------------------------------------- GET TYPE NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return read_state;
  }
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return read_state;
  }
  //PRINT TYPE NAME
  Type_Name[0] = buffer1[0];
  Type_Name[1] = buffer1[1];
  long singleweight = 0;
  for (uint8_t i = 2; i < 6; ++i)
  {
    singleweight = singleweight*10 + (buffer1[i]-48);
  }
  Single_Weight = singleweight;
  Serial.print(F("Type Name: "));
  Serial.println(Type_Name);
  Serial.print(F("Type Single Weight: "));
  Serial.println(Single_Weight);
  //---------------------------------------- GET WEIGHT

  byte buffer2[18];
  block = 4;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return read_state;
  }
  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return read_state;
  }
  //PRINT WEIGHT
  int shellweight = 0;
  for (uint8_t i = 1; i < 16; ++i) {
    // Serial.write(buffer2[i] );
    // Serial.println();
    // Serial.println(buffer2[i]);
    if(buffer2[i] == 32) break;
    shellweight =   shellweight*10 + (buffer2[i]-48);
  }
  Shell_Weight = shellweight;
  Serial.print(F("Shell Weight: "));
  Serial.println(Shell_Weight);
  //----------------------------------------
  Serial.println(F("**End Reading**\n"));
  read_state = 2;
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  return read_state;
}

bool RC522::write(){   //AA0010#  0#
  //初始化读卡状态
  //未读到卡为0，读到卡为1
  bool write_state = 0;
  //创建访问密钥，用于验证并访问 MIFARE Classic RFID标签
  //这里用默认卡密钥
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //block为卡的不同区域编号
  //len3为读到的字节数
  //status为判断对卡操作是否成功完成的状态变量
  byte block;
  byte len3;
  MFRC522::StatusCode status;

  // 如果传感器/读卡器上没有新卡，则复位循环。这可以在空闲时保存整个进程。
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return write_state;
  }

  // 选择一张卡片进行读取
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return write_state;
  }

  Serial.println(F("**Card Detected:**"));
  // 成功读取到卡片，将读卡状态设为1
  write_state = 1;
  
  //打印UID编号
  Serial.print(F("Card UID:"));    
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  //打印PICC类型
  Serial.print(F(" PICC type: "));   
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));  

  byte buffer3[34];
  //等待20秒从串口输入
  Serial.setTimeout(20000L) ;     
  // 提示:输入类型名称
  Serial.println(F("Type name, ending with #"));
  //从串口读入类型名称到buffer3，len为写入字节长度
  len3 = Serial.readBytesUntil('#', (char *) buffer3, 30) ; 
  // 将未满字节用空格填补
  for (byte i = len3; i < 30; i++) buffer3[i] = ' ';     

  block = 1;
  //选择读取区域和密钥进行身份验证，验证失败打印错误信息并提前终止
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return write_state;
  }
  else Serial.println(F("PCD_Authenticate() success: "));

  // 对前述验证成功的区域内的信息写入字节数组，写入失败打印错误信息并提前终止
  status = mfrc522.MIFARE_Write(block, buffer3, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return write_state;
  }
  else Serial.println(F("MIFARE_Write() success: "));

  block = 2;
  //选择读取区域和密钥进行身份验证，验证失败打印错误信息并提前终止
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return write_state;
  }

  // 对前述验证成功的区域内的信息写入字节数组的地址，写入失败打印错误信息并提前终止
  status = mfrc522.MIFARE_Write(block, &buffer3[16], 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return write_state;
  }
  else Serial.println(F("MIFARE_Write() success: "));

  byte buffer4[34];
  byte len4;
  // Ask personal data: First name
  Serial.println(F("Type Weight, ending with #"));
  len4 = Serial.readBytesUntil('#', (char *) buffer4, 20) ; // read first name from serial
  for (byte i = len4; i < 20; i++) buffer4[i] = ' ';     // pad with spaces

  block = 4;
  //选择读取区域和密钥进行身份验证，验证失败打印错误信息并提前终止
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return write_state;
  }

  // 对前述验证成功的区域内的信息写入字节数组，写入失败打印错误信息并提前终止
  status = mfrc522.MIFARE_Write(block, buffer4, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return write_state;
  }
  else Serial.println(F("MIFARE_Write() success: "));

  block = 5;
  //选择读取区域和密钥进行身份验证，验证失败打印错误信息并提前终止
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return write_state;
  }

  // 对前述验证成功的区域内的信息写入字节数组的地址，写入失败打印错误信息并提前终止
  status = mfrc522.MIFARE_Write(block, &buffer4[16], 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return write_state;
  }
  else Serial.println(F("MIFARE_Write() success: "));
  delay(1000); 

  //--------------成功完成读取----------------
  Serial.println(F("\n**End Reading**\n"));
  //停止响应当前正在运行的命令。
    //将 RFID 卡片置于休眠状态，以便进行下一个命令的执行。
  mfrc522.PICC_HaltA();
  //停止当前正在进行的加密。如果 RFID 模块正在与 RFID 卡片进行加密通信，
  //则此代码将停止加密，并将模块置于初始状态，以便进行下一个操作。
  mfrc522.PCD_StopCrypto1();
  //返回写卡状态
  return write_state;
}