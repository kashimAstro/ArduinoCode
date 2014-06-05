/* setup */
void init_setup_synth() {
  pinMode(LEDON,OUTPUT);
  pinMode(LEDOFF,OUTPUT);
  for( int i = 0; i < NUMBUTTON; i++ ) {
    pinMode(buttonPin[i],  INPUT);
  }
}

void sendMIDImsg(byte note, byte velocity) { 
    Serial.write((byte)0x90);
    Serial.write((byte)note);
    Serial.write((byte)velocity);
}

/* read state button */
void run_digital_button() {
  for( int i = 0; i < NUMBUTTON; i++ ) {
    buttonState[i] = digitalRead(buttonPin[i]);
    if(buttonState[i] == HIGH) {
      digitalWrite(LEDON,HIGH);
      sendMIDImsg(notes[i], VELOCITYON);
      boolseat=!boolseat;
    }
    else if(boolseat){
      sendMIDImsg(notes[i], VELOCITYOFF);
      digitalWrite(LEDON,LOW);
      boolseat=!boolseat;
    }
  }
}

/* read state analog */
void run_analog_red() {
  for( int i = 0; i < NUMANALOG; i++ ) {
    pressedState[i] = analogRead(analogPin[i]);
    if(pressedState[i] > 0) {
      GLOBAL_PRESS_MOMENT = pressedState[i];
 
      /* inizio nota */
      digitalWrite(LEDOFF,HIGH);
      sendMIDImsg(pressedState[i], 127);
 
      /* delay tra inizio nota e fine nota default 100ms or GLOBAL_PRESS_MOMENT */
      if(DEBUG==0){
        if( GLOBAL_PRESS_MOMENT > 0 ) { delay(GLOBAL_PRESS_MOMENT); } else { delay(100); }
      }
      
      /*termina nota */
      if(DEBUG==0)
        sendMIDImsg(0, 0);
      digitalWrite(LEDOFF,LOW);
    }
  }
}
