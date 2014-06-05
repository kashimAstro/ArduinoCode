
/*

 Ziggurats Motion Plus - Inertial measurement unit
 
 shoulder - spalla
 elbow    - gomito
 wrist    - polso
 hand     - mano
 hip      - anca
 knee     - ginocchio
 ankle    - caviglia
 
 */
void wmpOn(){
  Wire.beginTransmission(0x53);
  Wire.write(0xfe);
  Wire.write(0x04);
  Wire.endTransmission();
}

void wmpSendZero(){
  Wire.beginTransmission(0x52);
  Wire.write(0x00);
  Wire.endTransmission();
}

void calibrateZeroes(){
  for (int i=0;i<10;i++){
    wmpSendZero();
    Wire.requestFrom(0x52,6);
    for (int i=0;i<6;i++){
      data[i]=Wire.read();
    }
    yaw_calib+=(((data[3]>>2)<<8)+data[0])/10;
    pitch_calib+=(((data[4]>>2)<<8)+data[1])/10;
    roll_calib+=(((data[5]>>2)<<8)+data[2])/10;
  }
  Serial.print("Yaw0:");
  Serial.print(yaw_calib);
  Serial.print(" Pitch0:");
  Serial.print(pitch_calib);
  Serial.print(" Roll0:");
  Serial.println(roll_calib);
}

void receiveData(){
  wmpSendZero();
  Wire.requestFrom(0x52,6);
  for (int i=0;i<6;i++){
    data[i]=Wire.read(); 
  }
  yaw=((data[3]>>2)<<8)+data[0]-yaw_calib; 
  pitch=((data[4]>>2)<<8)+data[1]-pitch_calib; 
  roll=((data[5]>>2)<<8)+data[2]-roll_calib; 
}
