#include "Calibrate.h"

Calibrate::Calibrate(){};

void Calibrate::setpin_SCKDT(int p1, int p2) {
  pin_SCK = p1;
  pin_DT = p2;
  pinMode(pin_DT, INPUT);	
  pinMode(pin_SCK, OUTPUT);	
}

void Calibrate::set_range(int r) {
  range = r;
  GapValue = 128 * 16.777215 / r;
};

unsigned long Calibrate::Output_Weight(unsigned long ADS) {
  unsigned long difference = HX711_Read() - ADS;
	unsigned long RealWeight = (long)(difference/GapValue);
  if (RealWeight > 20000) RealWeight = 0;			
  return RealWeight;
};

unsigned long Calibrate::HX711_Read() {
  unsigned long AD_value=0;
	digitalWrite(pin_DT, HIGH);
	delayMicroseconds(1);
	digitalWrite(pin_SCK, LOW);
	delayMicroseconds(1);
  while(digitalRead(pin_DT));
   
  for(unsigned char i=0;i<24;++i) {
	  digitalWrite(pin_SCK, HIGH); 
		delayMicroseconds(1);
	  AD_value <<= 1; 
		digitalWrite(pin_SCK, LOW); 
		delayMicroseconds(1);
	  if(digitalRead(pin_DT)) ++AD_value; 
    // Serial.println(AD_value);
	} 
	// AD_value ^= 0x800000;

 	digitalWrite(pin_SCK, HIGH); 
	delayMicroseconds(1);
	digitalWrite(pin_SCK, LOW); 
	delayMicroseconds(1);

  // Serial.println(AD_value);
  return AD_value;
};

void Calibrate::Get_x_array(unsigned long ADS){
  int n=6;
  unsigned long standards[n];

  Serial.println("CARLIBRATING, NOW");
  delay(5000);
  Serial.println("START");
  delay(2000);
  for (int i=0; i<n; i++) {
    Serial.print(i+1);
    Serial.print("standards: ");
    delay(5000);
    standards[i] = Output_Weight(ADS);
    Serial.print(standards[i]);
    Serial.println("");
  }
  delay(4000); 

  for (int i=0; i<n; ++i) x[i]=standards[i];
};

void Calibrate::Get_kb(){
  int n=6;
  unsigned long y[n] = {5, 15, 35, 55, 105, 574}, sum_x = 0, sum_y = 0;
  for (unsigned long& yi:y) 
      sum_y+=yi;
    for (unsigned long& x_i:x) 
      sum_x+=x_i;
    unsigned long mean_x = sum_x/n, mean_y = sum_y/n;
    unsigned long k1=0, k2=0;
    for (int i=0; i<n; ++i) {
      k1+=x[i]*y[i];
      k2+=x[i]*x[i];
    }
    k = (k1-n*mean_x*mean_y)/(k2-n*mean_x*mean_x);
    b = mean_y - mean_x * k;

    coeffience k_out;
    coeffience b_out;

    k_out.value_out = k;
    b_out.value_out = b;

    for(int i=4; i<8; i++)    //判断是否与上次储存的k相同
      if (!(EEPROM.read(i)==k_out.value_in[i-4])) {
        Serial.print("newk:");
        Serial.println(k);
        for (int j=4; j<8; j++) 
          EEPROM.write(j, k_out.value_in[j-4]);
        break;
      }
        
    for(int i=8; i<12; i++)    //判断是否与上次储存的b相同
      if (!(EEPROM.read(i)==b_out.value_in[i-8])) {
        Serial.print("newb:");
        Serial.println(b);
        for (int j=i; j<12; j++) 
          EEPROM.write(j, b_out.value_in[j-8]);
        break;
      }
};

unsigned long Calibrate::Output_CalibratedWeight(unsigned long ADS){
  return k*Output_Weight(ADS)+b;
};

void Calibrate::kb_Initialize() {
  // clear_memory();
  coeffience k_arduino;
  coeffience b_arduino;
  
  for(int i=4; i<8; i++) {
    k_arduino.value_in[i-4] = EEPROM.read(i);
    b_arduino.value_in[i-4] = EEPROM.read(i+4);
  }

  k = k_arduino.value_out;
  b = b_arduino.value_out;
  Serial.print("k: ");
  Serial.println(k);
  Serial.print("b: ");
  Serial.println(b);
};