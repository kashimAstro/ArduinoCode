// power on Arduino
// Connect ESC signal wire to Pin B2 (Digital 10)
// Connect ESC groud wire to Arduino Gnd
// Start Serial Monitor
// Connect ESC 5v to Arduino 5v - ESC will start bleeping
// now conect ESC main power

#include <avr/interrupt.h> 
#include "TPC.h"

#define LED_PIN 13

const char Brake_0[] 	= "Off";
const char Brake_1[] 	= "On";

const char* Brake_Names[] = 	
{
  Brake_0,
  Brake_1
};

const char BatteryType_0[]	= "LiIon/LiPo";
const char BatteryType_1[]	= "NiMH/NiCd";

const char* BatteryType_Names[] = 	
{
  BatteryType_0,
  BatteryType_1
};

const char CutOff_Mode_0[] 	= "Soft-Cut";
const char CutOff_Mode_1[] 	= "Cut-Off";

const char* CutOff_Mode_Names[] = 	
{
  CutOff_Mode_0,
  CutOff_Mode_1
};

const char CutOff_Voltage_0[] 	= "Low";
const char CutOff_Voltage_1[] 	= "Medium";
const char CutOff_Voltage_2[] 	= "High";

const char* CutOff_Voltage_Names[] = 	
{
  CutOff_Voltage_0,
  CutOff_Voltage_1,
  CutOff_Voltage_2
};

const char Start_Mode_0[] 	= "Normal";
const char Start_Mode_1[] 	= "Soft";
const char Start_Mode_2[] 	= "Super Soft";

const char* Start_Mode_Names[] = 	
{
  Start_Mode_0,
  Start_Mode_1,
  Start_Mode_2
};

const char Timing_0[] 	= "Low";
const char Timing_1[] 	= "Medium";
const char Timing_2[] 	= "High";

const char* Timing_Names[] = 	
{
  Timing_0,
  Timing_1,
  Timing_2
};


unsigned short Initial_Settings;
TPC_settings_t	Initial_Settings_t;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  
  // -----------------------
  Serial.begin(115200);
  delay(500);
  
  Serial.println("Turnigy Plush");
  
  delay(1500);
  
  Serial.println("ESC Setup");
  Serial.println("Plug ESC Power");

  TPC_PIN_ON();
  TPC_PIN_INPUT();

  TPC_read_init(&Initial_Settings_t);

  Initial_Settings = TPC_struct_to_word(&Initial_Settings_t);
  
  Serial.print("Brake:");
  Serial.println(Brake_Names[Initial_Settings_t.brake]);

  Serial.print("Battery Type:");
  Serial.println(BatteryType_Names[Initial_Settings_t.battType]);

  Serial.print("Cutoff Mode:");
  Serial.println(CutOff_Mode_Names[Initial_Settings_t.cutoffType]);
  
  Serial.print("Cutoff Voltage:");
  Serial.println(CutOff_Voltage_Names[Initial_Settings_t.cutoffVoltage]);

  Serial.print("Start Mode:");
  Serial.println(Start_Mode_Names[Initial_Settings_t.startMode]);

  Serial.print("Timing:");
  Serial.println(Timing_Names[Initial_Settings_t.timingMode]);
   
}

void loop() {
  while(1) {
    delay(50);
  }
}


