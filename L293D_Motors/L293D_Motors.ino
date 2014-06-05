const int motor1Pin = 7;
const int motor2Pin = 5;

void setup() {
  pinMode(motor1Pin, OUTPUT); 
  pinMode(motor2Pin, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()>0){
    int val = Serial.read() - '0';

    if (val == 0) {
      digitalWrite(motor1Pin, 0);
      digitalWrite(motor2Pin, 1);
      Serial.print("orario: ");
    } 
    if (val == 1) {
      digitalWrite(motor1Pin, 1);
      digitalWrite(motor2Pin, 0);
      Serial.print("antiorario: ");
    }
    if (val == 2) {
      digitalWrite(motor1Pin, 0);
      digitalWrite(motor2Pin, 0);
      Serial.print("ferma: ");
    }
    Serial.print(val);
    Serial.println("");
  }
  delay(150);
}
