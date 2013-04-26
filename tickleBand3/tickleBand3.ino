/*
 * tickleBand3 
 * A standalone OZ prototye testing triggers at certain time of the day
 * Set the hour of a trigger using the trigger hours
 */

#include <Time.h>  
#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 
// set pin numbers
const int buttonPins[] = {A3, A1};
const int ticklePin = 6;
const int numInputs = 2;

int numberPresses = 0;
int lastButtonState[numInputs];

// T1262347200  //noon Jan 1 2010
// Trigger hours
#define NUM_TRIGGERS 4
int TriggerHours[] = {9,12,18,24};

void setup()  {
  Serial.begin(9600);
  for(int i=0; i<numInputs; i++){
     pinMode(buttonPins[i], INPUT); 
     digitalWrite(buttonPins[i], HIGH); 
     lastButtonState[i] = LOW;
  }
  pinMode(ticklePin, OUTPUT);
}

void loop(){  
  int reading[numInputs];
  
  
  for(int i = 0; i < numInputs; i++){
    reading[i] = digitalRead(buttonPins[i]); 
    // If the switch changed, due to noise or pressing:
    if (reading[i] != lastButtonState[i]) {
      // reset the debouncing timer
      if(reading[i] == HIGH){
        numberPresses++; 
      }
    } 
    // save the reading.  Next time through the loop,
    // it'll be the lastButtonState:
    lastButtonState[i] = reading[i];
  }
  if(Serial.available() ) 
  {
    processSyncMessage();
  }
  if(timeStatus() == timeNotSet) 
    Serial.println("w");
  else{
    boolean trigger = false;
    for(int i = 0; i< NUM_TRIGGERS; i++){
      if(hour() == TriggerHours[i]){
        trigger = true; 
      }
    }
    if(trigger){
      triggerTickle(); 
    }
  }
  stopTickle();
  Serial.println(String(hour()) + " h");
  Serial.println(String(numberPresses) + " p");
  delay(100);

}

void triggerTickle(){
  digitalWrite(ticklePin, HIGH);
}

void stopTickle(){
  digitalWrite(ticklePin, LOW); 
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void processSyncMessage() {
  // if time sync available from serial port, update time and return true
  while(Serial.available() >=  TIME_MSG_LEN ){  // time message consists of header & 10 ASCII digits
    char c = Serial.read() ; 
    Serial.print(c);  
    if( c == TIME_HEADER ) {       
      time_t pctime = 0;
      for(int i=0; i < TIME_MSG_LEN -1; i++){   
        c = Serial.read();          
        if( c >= '0' && c <= '9'){   
          pctime = (10 * pctime) + (c - '0') ; // convert digits to a number    
        }
      }   
      setTime(pctime);   // Sync Arduino clock to the time received on the serial port
    }  
  }
}
