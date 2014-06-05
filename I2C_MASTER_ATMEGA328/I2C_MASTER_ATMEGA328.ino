#include <Wire.h>
#include <MCP3008.h>

#define CS_PIN 12
#define CLOCK_PIN 9
#define MOSI_PIN 11
#define MISO_PIN 10

MCP3008 adc(CLOCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);

#define LED_PIN 13
byte x = 0;

void setup() {
  Wire.begin();
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);
}

void loop(){
  Wire.beginTransmission(9);
  Wire.write(x);
  Wire.endTransmission();
  digitalWrite(LED_PIN,HIGH);
  x++;
  if (x > 5) x=0;
 
  Serial.print("i2c:");
  Serial.println(x);
  int val = adc.readADC(0);
  Serial.println(val);
  
  delay(500);
  digitalWrite(LED_PIN,LOW);
  delay(100);
}
