#include "RC522.h"

RC522 rc522;
bool rflag=0;

void setup() {
  Serial.begin(9600);  
  rc522.initialize(9,10);
}

void loop() {
  switch(rflag){
    case 0: 
      while(1) {
        bool state = rc522.write();
        if(state==1)
          break;
      }   
      rflag=1;
      break;
    case 1:
      while(1) {
        bool state = rc522.read();
        if(state==1)
          break;
      }
      break;
  }
}
