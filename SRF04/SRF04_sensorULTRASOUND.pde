const int sendPin = 3;
const int pingPin = 2;

void setup() {
  Serial.begin(9600);
}

void loop(){
  long duration, inches, cm;

  pinMode(sendPin, OUTPUT);
  digitalWrite(sendPin, LOW);

  delayMicroseconds(2);
  digitalWrite(sendPin, HIGH);

  delayMicroseconds(5);
  digitalWrite(sendPin, LOW);

  pinMode(sendPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
}

long microsecondsToInches(long microseconds){
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}

