#include <Servo.h> 
#define DEBUG true

const int buttonPins[] = {A3, A1};
const int numInputs = 2;

char incomingByte = 0;
boolean DEBUG = false;

int led = 13;

void setup() 
{
  Serial.begin(9600);
  for(int i=0; i<numInputs; i++){
     pinMode(buttonPins[i], INPUT); 
     digitalWrite(buttonPins[i], HIGH); 
     lastButtonState[i] = LOW;
  }
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
        numberPresses++; 
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
    triggerTickle()
    digitalWrite(led,HIGH);
  }
  else{
    digitalWrite(led,LOW);
  }
  // Wait 100 milliseconds
  delay(200);
}

void triggerTickle(){
  
}

void sendTickle(){
  Serial.write('t');
}
