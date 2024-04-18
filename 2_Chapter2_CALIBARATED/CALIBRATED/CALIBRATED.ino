#include "Surface.h"
#include "Calibrate.h"

Surface YL_Surface;
Calibrate YL_Calibrated;

bool flag=1;

void setup() {
  Serial.begin(9600);
  YL_Calibrated.setpin_SCKDT(4, 5);
  YL_Calibrated.set_range(20);
  YL_Calibrated.kb_Initialize();
  YL_Surface.setpin_SCKDT(4, 5);
}

void loop() {
  if (flag) {
    YL_Calibrated.Get_x_array(YL_Surface.Get_Surface());
    YL_Calibrated.Get_kb();
    flag=0;
  }

  unsigned long CalibratedWeight = YL_Calibrated.Output_CalibratedWeight(YL_Surface.Get_Surface());
  Serial.println(CalibratedWeight);
  delay(1000);
}
