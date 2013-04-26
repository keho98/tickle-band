#include <Servo.h> 
#define DEBUG true

const int buttonPins[] = {A3, A1};
const int numInputs = 2;

char incomingByte = 0;

int led = 13;
int lastButtonState[numInputs];

/****servo variables ***/
const int servoPin0 = 8;
const int servoPin1 = 9;

Servo servo0;
Servo servo1;

int pos0 = 0;
int pos1 = 0;


void setup() 
{
  Serial.begin(9600);
  for(int i=0; i<numInputs; i++){
     pinMode(buttonPins[i], INPUT); 
     digitalWrite(buttonPins[i], HIGH); 
     lastButtonState[i] = LOW;
  }
  servo0.attach(servoPin0);
  servo1.attach(servoPin1);
  pinMode(led,OUTPUT);
}

void loop() 
{
  int reading[numInputs];
  for(int i = 0; i < numInputs; i++){
    reading[i] = digitalRead(buttonPins[i]); 
    // If the switch changed, due to noise or pressing:
    if (reading[i] != lastButtonState[i]) {
      // reset the debouncing timer
      if(reading[i] == HIGH){
        sendTickle();
      }
    } 
    // save the reading.  Next time through the loop,
    // it'll be the lastButtonState:
    lastButtonState[i] = reading[i];
  }
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    // say what you got:
    triggerTickle();
    digitalWrite(led,HIGH);
  }
  else{
    digitalWrite(led,LOW);
  }
  // Wait 100 milliseconds
  delay(200);
}

void triggerTickle(){
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

void sendTickle(){
  Serial.write('t');
}
