#include "DataCollect.h"

DataCollect::DataCollect(int p1, int p2, int r) {
  ps = PressureSensor(p1, p2, r);
  ps.Set_Surfacevalue();
};

void DataCollect::Output_data() {
  if (Serial.available()>0) {
    while (Serial.available()>0)
      Serial.read();
    ps.Set_Weight();
    ps.Output_Weight();
  }
}