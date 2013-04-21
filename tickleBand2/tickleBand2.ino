#define IO_PAIRS 3
int analogOutputPins[] = {3,5,6};
int analogInputPins[] = {0,1,2};
char incomingByte = 0;
boolean DEBUG = false;

void setup() 
{
  Serial.begin(9600);
  for(int i=0; i<IO_PAIRS; i++){
    pinMode(analogOutputPins[i], OUTPUT);
  }
  analogWrite(6, 255);
}

void loop() 
{
  if(DEBUG){
    Serial.println(String(analogRead(analogInputPins[0])) + " " + analogRead(analogInputPins[1]) + " " + analogRead(analogInputPins[2]));
  }
//  for(int i=0; i<IO_PAIRS -1; i++){
//    int pressureValue = analogRead(analogInputPins[i]);
//    if(pressureValue > 500){
//      analogWrite(analogOutputPins[i], 110);
//      Serial.println(i, DEC);
//    }
//    else{
//      analogWrite(analogOutputPins[i], 255);
//    }
//  }  
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    // say what you got:
    analogWrite(analogOutputPins[0], 110);
    analogWrite(analogOutputPins[1], 110);
    analogWrite(analogOutputPins[2], 110);
  }
  else{
    analogWrite(analogOutputPins[0], 255);
    analogWrite(analogOutputPins[1], 255);
    analogWrite(analogOutputPins[2], 255);
  }
  // Wait 100 milliseconds
  delay(200);
}
