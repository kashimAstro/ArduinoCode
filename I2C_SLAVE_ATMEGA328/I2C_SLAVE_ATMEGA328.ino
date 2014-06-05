#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define sclk 13
#define mosi 11
#define cs   10
#define dc   9
#define rst  8

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);
float p = 3.1415926;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  tft.initR(INITR_REDTAB);
  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;
  Serial.println(time, DEC);
  tftPrintTest();
  delay(100);
}

void loop() {
  Wire.requestFrom(2, 5);
  while(Wire.available()) { 
    char c = Wire.read();
    Serial.print(c);
    delay(100);
  }
}

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(2);
  tft.print("Motori");
  tft.setCursor(0, 30);
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(1);
  tft.print(" x:");
  tft.print(123);
  tft.print(" y:");
  tft.print(453);
  tft.print(" z:");
  tft.print(24.2);
  tft.setCursor(0, 50);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(1);
  tft.print(" feedr:");
  tft.print(100);
  tft.print(" speed:");
  tft.print(1000);
}
