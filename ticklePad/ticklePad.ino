// #
// # Editor    : Jiang from DFRobot
// # Data      : 19.11.2012
// # E-Mail    : jianghao0716@gmail.com
 
// # Product name  : Capacitive touch pad 
// # Version  : 0.4
// # Power supply: 3.3v
// # Connection:
// #       SDA (MPR121) -> PIN A4 (Arduino)
// #       SCL (MPR121) -> PIN A5 (Arduino)
// #       IRQ (MPR121) -> PIN A2 (Arduino) 
 
#include <Wire.h>
#include <mpr121.h>
#include <Servo.h> 

#define MAX_X 9
#define MAX_Y 13
#define MIN_X 1
#define MIN_Y 1

#define MICRO_MAX 2200
#define MICRO_MIN 800

int X ;           // X-coordinate
int Y ;           // Y-coordinate

Servo servoX;
Servo servoY;
const int servoPinX = 8;
const int servoPinY = 6;
 
// =========  setup  =========
void setup()
{ 
  //  initialize function
  Serial.begin(9600);
  Wire.begin();
  CapaTouch.begin();
  //Initialize servos
  servoX.attach(servoPinX);
  servoY.attach(servoPinY);
  delay(500);
  Serial.println("START"); 
}

void setX(int x){
  //Scale x
  float microSeconds = float(MICRO_MAX - MICRO_MIN) /float(MAX_X - MIN_X) * x + MICRO_MIN;
  servoX.writeMicroseconds(int(microSeconds));
  Serial.println(int(microSeconds));
}

void setY(int y){
 float microSeconds = float(MICRO_MAX - MICRO_MIN) / float(MAX_Y - MIN_Y) * y + MICRO_MIN;
 servoY.writeMicroseconds(int(microSeconds)); 
 Serial.println(int(microSeconds));
}
 
// =========  loop  =========
void loop()
{   
  X=CapaTouch.getX();              // Get X position.
  Y=CapaTouch.getY();              // Get Y position.
  if(X>=MIN_X&&X<=MAX_X&&Y>=MIN_Y&&Y<=MAX_Y)
   {                                 // Determine whether in the range.If not,do nothing.
      Serial.print(X);
      Serial.print(",");
      Serial.println(Y); 
      setX(X);
      setY(Y);
   }
  delay(200);
}
