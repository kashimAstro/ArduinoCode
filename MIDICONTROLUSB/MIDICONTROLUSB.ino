#define DEBUG 0

#define CHANNEL     0x90
#define VELOCITYON  0x55
#define VELOCITYOFF 0x00
#define NUMBUTTON   10
#define NUMANALOG   4
#define LEDON       7
#define LEDOFF      8
boolean boolseat = false;
int GLOBAL_PRESS_MOMENT = 0;
int notes[]        = { 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44 };  /* digital note on  */                                                      
int noteONanalog[] = { 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5 };          /* analog note on   */
int buttonPin[]    = { 2, 3, 4, 5, 6, 9, 10, 11, 12, 13 };            /* digital button   */
int analogPin[]    = { A0, A1, A2, A3, A4, A5  };                     /* analog sensor    */
int buttonState[NUMBUTTON];
int pressedState[NUMANALOG];

void setup(void) {
  if(DEBUG==0)  Serial.begin(31250);
  else          Serial.begin(9600);
  init_setup_synth();
}

void loop(void){
  run_digital_button();
  //run_analog_red();
  if(DEBUG!=0)
    delay(100);
}
