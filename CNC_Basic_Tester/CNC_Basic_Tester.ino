int motorPin1 = 8;
int motorPin2 = 9;
int motorPin3 = 10;
int motorPin4 = 11;

int xmotorPin1 = 4;
int xmotorPin2 = 5;
int xmotorPin3 = 6;
int xmotorPin4 = 7;

int delayTime = 50;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  pinMode(xmotorPin1, OUTPUT);
  pinMode(xmotorPin2, OUTPUT);
  pinMode(xmotorPin3, OUTPUT);
  pinMode(xmotorPin4, OUTPUT);
}

void loop() {
  if(Serial.available()) {
    char val = Serial.read();
    if(val == '1')
      stepper_A_right();
    if(val == '2')
      stepper_A_left();

    if(val == '3')
      stepper_B_right();
    if(val == '4')
      stepper_B_left();
  }
}

void stepper_A_right() {
  Serial.println("motor A right");
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(delayTime);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(delayTime);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(delayTime);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(delayTime);
}

void stepper_A_left() {
  Serial.println("motor A left");
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(delayTime);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(delayTime);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(delayTime);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(delayTime);
}

void stepper_B_right() {
  Serial.println("motor B right");
  digitalWrite(xmotorPin1, HIGH);
  digitalWrite(xmotorPin2, LOW);
  digitalWrite(xmotorPin3, LOW);
  digitalWrite(xmotorPin4, LOW);
  delay(delayTime);
  digitalWrite(xmotorPin1, LOW);
  digitalWrite(xmotorPin2, LOW);
  digitalWrite(xmotorPin3, HIGH);
  digitalWrite(xmotorPin4, LOW);
  delay(delayTime);
  digitalWrite(xmotorPin1, LOW);
  digitalWrite(xmotorPin2, HIGH);
  digitalWrite(xmotorPin3, LOW);
  digitalWrite(xmotorPin4, LOW);
  delay(delayTime);
  digitalWrite(xmotorPin1, LOW);
  digitalWrite(xmotorPin2, LOW);
  digitalWrite(xmotorPin3, LOW);
  digitalWrite(xmotorPin4, HIGH);
  delay(delayTime);
}

void stepper_B_left() {
  Serial.println("motor B left");
  digitalWrite(xmotorPin1, LOW);
  digitalWrite(xmotorPin2, LOW);
  digitalWrite(xmotorPin3, LOW);
  digitalWrite(xmotorPin4, HIGH);
  delay(delayTime);
  digitalWrite(xmotorPin1, LOW);
  digitalWrite(xmotorPin2, HIGH);
  digitalWrite(xmotorPin3, LOW);
  digitalWrite(xmotorPin4, LOW);
  delay(delayTime);
  digitalWrite(xmotorPin1, LOW);
  digitalWrite(xmotorPin2, LOW);
  digitalWrite(xmotorPin3, HIGH);
  digitalWrite(xmotorPin4, LOW);
  delay(delayTime);
  digitalWrite(xmotorPin1, HIGH);
  digitalWrite(xmotorPin2, LOW);
  digitalWrite(xmotorPin3, LOW);
  digitalWrite(xmotorPin4, LOW);
  delay(delayTime);
}



