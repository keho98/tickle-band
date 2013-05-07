/*
 * tickleBand4
 * A standalone OZ prototye testing triggers at certain time of the day
 * Hard code the time manually, then give power to the clock.
 */

#include <Time.h> 
#include <Servo.h> 
#define DEBUG true
#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 
// set pin numbers
const int buttonPins[] = {
  A3, A1};
const int numInputs = 2;
const int servoPin0 = 8;
const int servoPin1 = 6; 

Servo servo0;
Servo servo1;

int pos0 = 0;
int pos1 = 0;
int led = 13;

int numberPresses = 0;
int lastButtonState[numInputs];

// T1262347200  //noon Jan 1 2010
// Trigger hours
#define NUM_TRIGGERS 4
int TriggerHours[] = {
  9,12,14,15,18,24};

void setup()  {
  ADCSRA = 0;
  PRR = B10010101;
  Serial.begin(9600);
  for(int i=0; i<numInputs; i++){
    pinMode(buttonPins[i], INPUT); 
    digitalWrite(buttonPins[i], HIGH); 
    lastButtonState[i] = LOW;
  }
  //Set time HERE
  //setTime(hr,min,sec,day,month,yr);
  setTime(12,15,0,5,5,2013);
  pinMode(led, OUTPUT);
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
        if(DEBUG) triggerTickle();
      }
    } 
    // save the reading.  Next time through the loop,
    // it'll be the lastButtonState:
    lastButtonState[i] = reading[i];
  }
  if(timeStatus() == timeNotSet) 
    Serial.println("w");
  else{
    boolean trigger = false;
    for(int i = 0; i< NUM_TRIGGERS; i++){
      if(hour() == TriggerHours[i] && second() == 15){
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
  if(DEBUG) digitalWrite(led, HIGH);
  servo0.attach(servoPin0);
  servo1.attach(servoPin1);
  for(pos0 = 0; pos0 < 180; pos0 += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo0.write(pos0);
    servo1.write(pos0);    // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos0 = 180; pos0>=1; pos0-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servo0.write(pos0); 
    servo1.write(pos0);    // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  } 
}

void stopTickle(){
  servo0.detach();
  servo1.detach();
  if(DEBUG) digitalWrite(led, LOW);
}
