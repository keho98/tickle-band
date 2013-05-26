/*
 * tickleBand5
 * A standalone OZ prototye testing triggers at certain time of the day
 * FOR LINEAR ACTUATOR
 */

#include <Time.h> 
#include <Servo.h> 
#define DEBUG false
#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 
// set pin numbers
const int buttonPins[] = {
  A1};
const int numInputs = 1;
const int servoPin0 = 6;
//const int servoPin1 = 6;

const int squeezePin0 = 9;

const int motorPin = 3;

Servo servo0;
Servo squeeze0;
//Servo servo1;

int pos0 = 0;
int pos1 = 0;
int led = 13;

int numberPresses = 0;
int lastButtonState[numInputs];

// T1262347200  //noon Jan 1 2010
// Trigger hours
#define NUM_TRIGGERS 0
int TriggerHours[] = {9,12,18,19,20,23};

void setup()  {
//  ADCSRA = 0;
//  PRR = B10010101;
  Serial.begin(9600);
  for(int i=0; i<numInputs; i++){
    pinMode(buttonPins[i], INPUT); 
    digitalWrite(buttonPins[i], HIGH); 
    lastButtonState[i] = LOW;
  }
  //Set time HERE
  //setTime(hr,min,sec,day,month,yr);
  setTime(18,29,0,5,5,2013);
  pinMode(led, OUTPUT);
  pinMode(motorPin, OUTPUT);
}

void loop(){  
  int reading[numInputs];
  for(int i = 0; i < numInputs; i++){
    reading[i] = getReading(buttonPins[i]); 
    if(DEBUG) Serial.println(String(getReading(buttonPins[i])));
    // If the switch changed, due to noise or pressing:
    if (reading[i] != lastButtonState[i]) {
      // reset the debouncing timer
      if(reading[i] == 2){
        numberPresses++; 
        Serial.println("s");
        triggerSqueeze();
      }
      else if(reading[i] == 1){
        numberPresses++;
        Serial.println("t");
        triggerVibe();
        triggerTickle();
        //stopTickle();
      }
    }
    else{
     Serial.println(""); 
    }
    // save the reading.  Next time through the loop,
    // it'll be the lastButtonState:
    lastButtonState[i] = reading[i];
  }
  analogWrite(motorPin, float(1024 - analogRead(A1))/1024*255);
  if(Serial.available() > 0){
    Serial.read();
    triggerTickle();
    stopTickle();
  }
  if(DEBUG) Serial.println(String(hour()) + " h");
  if(DEBUG) Serial.println(String(numberPresses) + " p");
  delay(20);
}

int getReading(int pin){
   int reading = analogRead(pin); 
   if(DEBUG) Serial.println(reading);
   int output = 0;
   if(reading < 500){
     output = 1;
   }
   if(reading < 200){
     output = 2;
   }
   return output;
}

//void triggerTickle(){
//  if(DEBUG) digitalWrite(led, HIGH);
//  servo0.attach(servoPin0);
//  servo1.attach(servoPin1);
//  for(pos0 = 0; pos0 < 180; pos0 += 1)  // goes from 0 degrees to 180 degrees 
//  {                                  // in steps of 1 degree 
//    servo0.write(pos0);
//    servo1.write(pos0);    // tell servo to go to position in variable 'pos' 
//    delay(10);                       // waits 15ms for the servo to reach the position 
//  } 
//  for(pos0 = 180; pos0>=1; pos0-=1)     // goes from 180 degrees to 0 degrees 
//  {                                
//    servo0.write(pos0); 
//    servo1.write(pos0);    // tell servo to go to position in variable 'pos' 
//    delay(10);                       // waits 15ms for the servo to reach the position 
//  } 
//}

void triggerVibe(){
 digitalWrite(motorPin, HIGH);
 delay(500);
 digitalWrite(motorPin, LOW); 
}

void triggerSqueeze(){
  squeeze0.attach(squeezePin0);
  //servo1.attach(servoPin1);
  for(int pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      squeeze0.write(pos);    // tell servo to go to position in variable 'pos' 
      //servo1.write(pos);
      delay(15);                       // waits 15ms for the servo to reach the position 
    } 
    for(int pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      squeeze0.write(pos);              // tell servo to go to position in variable 'pos' 
      //servo1.write(pos);
      delay(15);                       // waits 15ms for the servo to reach the position 
    }   
}

void triggerTickle(){
  digitalWrite(led, HIGH);
  servo0.attach(servoPin0);
  //servo1.attach(servoPin1);
  for(int pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      servo0.write(pos);    // tell servo to go to position in variable 'pos' 
      //servo1.write(pos);
      delay(15);                       // waits 15ms for the servo to reach the position 
    } 
    for(int pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      servo0.write(pos);              // tell servo to go to position in variable 'pos' 
      //servo1.write(pos);
      delay(15);                       // waits 15ms for the servo to reach the position 
    } 
  servo0.detach();
  digitalWrite(led,LOW);
}

void stopTickle(){
  servo0.writeMicroseconds(1500);
  //servo1.writeMicroseconds(1500);
  delay(1500);
  servo0.detach();
  //servo1.detach();
  digitalWrite(led, LOW);
}
