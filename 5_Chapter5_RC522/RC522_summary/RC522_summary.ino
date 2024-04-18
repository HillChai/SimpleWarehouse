#include "master.h"
#include "transform.h"
#include "Surface.h"
#include "Calibrate.h"
#include "Oled.h"
#include "RC522.h"

master m1;
Surface YL_Surface;
Calibrate YL_Calibrated;
transform tf;
Oled oled;
RC522 rc522;

long numbefore=0, numnow=1;
char te[3];
unsigned long Sweight;
bool rflag=1;  //1 ---> read; 0 ---> write

void setup() {
  Serial.begin(9600);
  m1.initialize(8);    //8needschanged
  YL_Calibrated.setpin_SCKDT(4, 5);
  YL_Calibrated.set_range(20);
  YL_Calibrated.kb_Initialize();
  oled.initialize();  
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
  for (int i=0; i<sizeof(rc522.Type_Name);i++) te[i]=rc522.Type_Name[i];
  Sweight=rc522.Single_Weight;

  numbefore = numnow;
  unsigned long CalibratedWeight = YL_Calibrated.Output_CalibratedWeight(YL_Surface.Get_Surface());
  numnow = ceil(CalibratedWeight/Sweight);

  bool flag= 1;
  // bool flag= (numbefore==numnow?0:1);
  if(flag){
  tf.initialize(te, m1.address, numnow, CalibratedWeight);
  tf.pack();
  digitalWrite(3,HIGH);
  m1.send(9, tf.Transmission_Information);
  Serial.println(tf.Transmission_Information);
  oled.showIIC(te, numnow);
  digitalWrite(3,LOW);
  }

  delay(3000);
}

