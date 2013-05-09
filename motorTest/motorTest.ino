
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
} 
 
 
void loop() 
{ 
  for(int i = 0; i < 255; i++){
    analogWrite(9,i);
    delay(200); 
  }
} 
