#define IO_PAIRS 3
int analogOutputPins[] = {3,5,6};
int analogInputPins[] = {0,1,2};
char incomingByte = 0;
boolean DEBUG = true;
int led = 2;

void setup() 
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);  
  //analogWrite(6, 255);
}

void loop() 
{
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    // say what you got:
    digitalWrite(led, HIGH); 
  }
  else{
   digitalWrite(led, LOW); 
  }
  // Wait 100 milliseconds
  delay(100);
}
