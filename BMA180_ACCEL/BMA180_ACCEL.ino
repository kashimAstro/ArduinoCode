#include <Wire.h> 

void setup() { 
  Serial.begin(115200); 
  Wire.begin();    

  AccelerometerInit();
  GyroInit();   
} 

void AccelerometerInit(){ 
  Wire.beginTransmission(0x40);
  Wire.write(0x10); 
  Wire.write(0xB6); 
  Wire.endTransmission(); 
  delay(10); 
   
  Wire.beginTransmission(0x40);
  Wire.write(0x0D); 
  Wire.write(0x10); 
  Wire.endTransmission(); 
   
  Wire.beginTransmission(0x40);
  Wire.write(0x20);
  Wire.endTransmission(); 
  Wire.requestFrom(0x40, 1); 
  byte data = Wire.receive();
  Wire.beginTransmission(0x40);
  Wire.write(0x20); 
  Wire.write(data & 0x0F);
  Wire.endTransmission(); 
   
  Wire.beginTransmission(0x40);
  Wire.write(0x35); 
  Wire.endTransmission(); 
  Wire.requestFrom(0x40, 1); 
  data = Wire.receive(); 
  Wire.beginTransmission(0x40);
  Wire.write(0x35); 
  Wire.write(data & 0xF1) | 0x04);
  Wire.endTransmission(); 
} 

void AccelerometerRead() { 
  Wire.beginTransmission(0x40);
  Wire.write(0x02);
  Wire.endTransmission(); 
  Wire.requestFrom(0x40, 6); 
  Serial.print("Accelerometer: X = "); 
  short data = Wire.receive(); 
  data += Wire.receive() << 8; 
  Serial.print(data); 
  Serial.print(" , Y = "); 
  data = Wire.receive(); 
  data += Wire.receive() << 8; 
  Serial.print(data); 
  Serial.print(" , Z = "); 
  data = Wire.receive(); 
  data += Wire.receive() << 8; 
  Serial.print(data); 
  Serial.println(); 
} 

void GyroInit() 
{ 
  Wire.beginTransmission(0x69);
  Wire.write(0x3E); 
  Wire.write(0x80); 
  Wire.endTransmission(); 
  
  Wire.beginTransmission(0x69);
  Wire.write(0x16); 
  Wire.write(0x1D); 
  Wire.endTransmission(); 
   
  Wire.beginTransmission(0x69);
  Wire.write(0x3E); 
  Wire.write(0x01); 
  Wire.endTransmission(); 
} 

void GyroRead(){ 
  Wire.beginTransmission(0x69);
  Wire.write(0x1D);
  Wire.endTransmission(); 
  Wire.requestFrom(0x69, 6); 
  short data = Wire.receive() << 8; 
  data += Wire.receive(); 
  Serial.print("Gyro: X = "); 
  Serial.print(data); 
  Serial.print(" , Y = "); 
  data = Wire.receive() << 8; 
  data += Wire.receive(); 
  Serial.print(data); 
  Serial.print(" , Z = "); 
  data = Wire.receive() << 8; 
  data += Wire.receive(); 
  Serial.print(data); 
  Serial.println(); 
} 

void loop() {
  AccelerometerRead();
  GyroRead();  
  delay(500);
}
