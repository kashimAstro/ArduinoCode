int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
 
int ispeed;
int output;
boolean up;
 
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
 
void loop() {
  up = true;
  output = 1;
  ispeed = 40;
 
  for (int j = 0; j < 253; j++){
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, output);
      digitalWrite(latchPin, HIGH);
      if (up){output = output << 1;}
      else {output = output >> 1;}
      if ((output == 0b10000000) || (output == 0b00000001)){up = !up;}
      delay(ispeed);
  }
 
  for (int j = 0; j < 200; j++){
    output = 1;
    for (int i = 0; i < 8; i++) {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, output);
      digitalWrite(latchPin, HIGH);
      output = output << 1;
      delay(ispeed);
 
    }
    if(ispeed > 1){ispeed = ispeed-1;}
  }
 
  ispeed = 250;
  for (output = 0; output < 256; output++){
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, output);
      digitalWrite(latchPin, HIGH);
      delay(ispeed);
  }
}
