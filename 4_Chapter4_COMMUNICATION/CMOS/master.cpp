#include "master.h"

master::master(){};

void master::initialize(int add) {
  address=add;
  Wire.begin(add);
};

void master::send(int add, char *data) {
  Wire.beginTransmission(add);
  Wire.write(data);
  Wire.endTransmission(add);
};
