#pragma once

#include "Master.h"

class Slave : public Master{
private:
static String Data_received;

public:
static int address_to_send;

  Slave(int add);
  void init();
  void feedback();
static void slave_receiveEvent(int howmany);
};