/**
 * HTTP Client. 
 * 
 * Starts a network client that connects to a server on port 80,
 * sends an HTTP 1.0 GET request, and prints the results. 
 *
 * Note that this code is not necessary for simple HTTP GET request:
 * Simply calling loadStrings("http://www.processing.org") would do
 * the same thing as (and more efficiently than) this example.
 * This example is for people who might want to do something more 
 * complicated later.
 */
 

import processing.net.*;
import processing.serial.*;

Serial myPort;
String data[];
final String myBand = "3";
final String theirBand ="4";

void setup() {
  println(Serial.list());
  myPort =  new Serial(this, Serial.list()[10], 9600); //Change this line to the correct serial port
}

void draw() {
  data = loadStrings("http://tickle-node.herokuapp.com/band?id=" + myBand);
  for (int i = 0 ; i < data.length; i++) {
    myPort.write(int(data[i]));
    print("writing");
  }
  //New data available
  if(myPort.available() > 0){
    String serialData = myPort.readStringUntil('\n');
    if(serialData != null) println(serialData);
    data = loadStrings("http://tickle-node.herokuapp.com/set_state?band=" + theirBand + "&state=" + serialData);
    for(int i = 0; i < data.length; i++){
     if(!data.equals("Success")){
        print(data);
     } 
    }
  }
  delay(200);
}

