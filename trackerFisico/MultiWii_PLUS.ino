#include <Wire.h>

#define PIN_ON_A 6

byte data[6];
int yaw, pitch, roll;
int yaw_calib, pitch_calib, roll_calib;

boolean START = false;
boolean STOP_INIT = true;

void setup(){
  Serial.begin(115200);
  Serial.println("WM+ tester");
  //pinMode(PIN_ON_A,OUTPUT);
  //digitalWrite(PIN_ON_A,HIGH);
  Wire.begin();
  wmpOn();
  calibrateZeroes();

  delay(1000);
}

void loop(){
  receiveData();
  Serial.print("yaw:");
  Serial.print(yaw);
  Serial.print("  pitch:");
  Serial.print(pitch);
  Serial.print("  roll:");
  Serial.println(roll);
  delay(100);
}



