#include "master.h"
#include "transform.h"
#include "Surface.h"
#include "Calibrate.h"
#include "Oled.h"

master m1;
Surface YL_Surface;
Calibrate YL_Calibrated;
transform tf;
Oled oled;

long numbefore=0, numnow=1;
char te[3] = {'A','A','\0'}; 
unsigned long Sweight=10;

void setup() {
  Serial.begin(9600);
  m1.initialize(10);    //9is the first
  YL_Calibrated.setpin_SCKDT(4, 5);
  YL_Calibrated.set_range(20);
  YL_Calibrated.kb_Initialize();
  oled.initialize();
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
}

void loop() {
  numbefore = numnow;
  unsigned long CalibratedWeight = YL_Calibrated.Output_CalibratedWeight(YL_Surface.Get_Surface());
  numnow = ceil(CalibratedWeight/Sweight);

  bool flag= (numbefore==numnow?0:1);
  if(flag){
    tf.pack(te, m1.address, numnow, CalibratedWeight);
    m1.send(8, tf.Transmission_Information);
    Serial.println(tf.Transmission_Information);
    oled.showIIC(te, numnow);
    digitalWrite(3,LOW);
  }

  delay(3000);
}
