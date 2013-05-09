/**
 * Simple Read
 * 
 * Read data from the serial port and change the color of a rectangle
 * when a switch connected to a Wiring or Arduino board is pressed and released.
 * This example works with the Wiring / Arduino program that follows below.
 */


import processing.serial.*;

final int port0 = 6;
final int port1 = 4;

Serial myPort;  // Create object from Serial class
Serial myPort1;
int val;      // Data received from the serial port

void setup() 
{
  size(200, 200);
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  println(Serial.list());
  String portName = Serial.list()[port0];
  String portName1 = Serial.list()[port1];
  myPort = new Serial(this, portName, 57600);
  myPort1 = new Serial(this,portName1, 57600);
}

void draw()
{
  if(myPort.available() > 0) {  // If data is available,         // read it and store it in val
    println("Reading from 2");
    char tmp = char(myPort.read());
    println(tmp);
    myPort1.write(tmp);
  }
  if(myPort1.available() > 0){
    println("Reading from 1");
    char tmp = char(myPort1.read());
    println(tmp);
    myPort.write(tmp); 
  }
  background(255);             // Set background to white
  if (val == 0) {              // If the serial value is 0,
    fill(0);                   // set fill to black
  } 
  else {                       // If the serial value is not 0,
    fill(204);                 // set fill to light gray
  }
  rect(50, 50, 100, 100);
  delay(10);
}



/*

// Wiring / Arduino Code
// Code for sensing a switch status and writing the value to the serial port.

int switchPin = 4;                       // Switch connected to pin 4

void setup() {
  pinMode(switchPin, INPUT);             // Set pin 0 as an input
  Serial.begin(9600);                    // Start serial communication at 9600 bps
}

void loop() {
  if (digitalRead(switchPin) == HIGH) {  // If switch is ON,
    Serial.print(1, BYTE);               // send 1 to Processing
  } else {                               // If the switch is not ON,
    Serial.print(0, BYTE);               // send 0 to Processing
  }
  delay(100);                            // Wait 100 milliseconds
}

*/
