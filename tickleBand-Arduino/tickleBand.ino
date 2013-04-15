int analogPin = 3;
int motorPin = 3;
int incomingByte = 0;
int DEBUG = false;

void setup() 
{
  Serial.begin(9600);
  pinMode(A3, OUTPUT);
}

void loop() 
{
  // Read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  int pressureValue = analogRead(A4);
  if(pressureValue > 500){
    analogWrite(A3, 130);
  }
  else{
    analogWrite(A3, 0);
  }  
  if (Serial.available() > 0) {
          // read the incoming byte:
          incomingByte = Serial.read();

          // say what you got:
          Serial.print("I received: ");
          Serial.println(incomingByte, DEC);
  }
  // Print out the value you read:
  if(DEBUG) Serial.println("Piezo: " + String(sensorValue) + "Pressure: " + String(pressureValue));
  // Wait 100 milliseconds
  delay(100);
}
