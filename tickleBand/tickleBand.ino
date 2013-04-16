#define IO_PAIRS 3
int analogOutputPins[] = {3,5,6};
int analogInputPins[] = {0,1,2};
int incomingByte = 0;
int DEBUG = false;

void setup() 
{
  Serial.begin(9600);
  for(int i=0; i<IO_PAIRS; i++){
    pinMode(analogOutputPins[i], OUTPUT);
  }
}

void loop() 
{
  for(int i=0; i<IO_PAIRS; i++){
    int pressureValue = analogRead(analogInputPins[i]);
    if(pressureValue > 500){
      analogWrite(analogOutputPins[i], 130);
    }
    else{
      analogWrite(analogOutputPins[i], 0);
    }
  }  
  if (Serial.available() > 0) {
          // read the incoming byte:
          incomingByte = Serial.read();
          // say what you got:
          Serial.print("I received: ");
          Serial.println(incomingByte, DEC);
  }
  // Wait 100 milliseconds
  delay(100);
}
