/*

magnetometro - arduino
vcc   --------- 3.3v
gnd   --------- gnd
sda   --------- A4
scl   --------- A5
int   --------- -

*/

#include <Wire.h>

#define MAG_ADDR  0x0E

void setup() {
  Wire.begin();
  Serial.begin(9600);
  config();
}

void loop() {
  print_values();
  delay(5);
}

void config(void){
  Wire.beginTransmission(MAG_ADDR);
  Wire.write(0x11);
  Wire.write(0x80);
  Wire.endTransmission();
  delay(15);
  Wire.beginTransmission(MAG_ADDR);
  Wire.write(0x10);
  Wire.write(1);
  Wire.endTransmission();
}

void print_values(void) {
  Serial.print("x=");
  Serial.print(readx()); 
  Serial.print(",");  
  Serial.print("y=");    
  Serial.print(ready());
  Serial.print(",");       
  Serial.print("z=");    
  Serial.println(readz());      
}

int readx(void) {
  int xl, xh;
  Wire.beginTransmission(MAG_ADDR);
  Wire.write(0x01);
  Wire.endTransmission();
  delayMicroseconds(2);
  Wire.requestFrom(MAG_ADDR, 1);
  while(Wire.available()) { 
    xh = Wire.read();
  }
  delayMicroseconds(2);
  Wire.beginTransmission(MAG_ADDR);
  Wire.write(0x02);
  Wire.endTransmission();
  delayMicroseconds(2);
  Wire.requestFrom(MAG_ADDR, 1);
  while(Wire.available()) { 
    xl = Wire.read();
  }
  int xout = (xl|(xh << 8));
  return xout;
}

int ready(void) {
  int yl, yh;
  Wire.beginTransmission(MAG_ADDR);
  Wire.write(0x03);
  Wire.endTransmission();
  delayMicroseconds(2);
  Wire.requestFrom(MAG_ADDR, 1);
  while(Wire.available()) { 
    yh = Wire.read();
  }
  delayMicroseconds(2);
  Wire.beginTransmission(MAG_ADDR);
  Wire.write(0x04);
  Wire.endTransmission();
  delayMicroseconds(2);
  Wire.requestFrom(MAG_ADDR, 1);
  while(Wire.available()) { 
    yl = Wire.read();
  }
  int yout = (yl|(yh << 8));
  return yout;
}

int readz(void){
  int zl, zh;
  
  Wire.beginTransmission(MAG_ADDR);
  Wire.write(0x05);
  Wire.endTransmission();
  delayMicroseconds(2);
  Wire.requestFrom(MAG_ADDR, 1);
  while(Wire.available()) { 
    zh = Wire.read();
  }
  delayMicroseconds(2); 
  Wire.beginTransmission(MAG_ADDR);
  Wire.write(0x06);
  Wire.endTransmission();
  delayMicroseconds(2);
  Wire.requestFrom(MAG_ADDR, 1); 
  while(Wire.available()) {
    zl = Wire.read();
  }
  int zout = (zl|(zh << 8));
  return zout;
}
