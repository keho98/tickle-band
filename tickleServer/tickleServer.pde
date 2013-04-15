/**
 * Chat Server 
 * by Tom Igoe. 
 * 
 * Press the mouse to stop the server.
 */
 

import processing.net.*;
import processing.serial.*;

int port = 8888;
boolean myServerRunning = true;
int bgColor = 0;
int direction = 1;
int textLine = 60;
boolean toggleOn = true;
Serial myPort;
Server myServer;

void setup()
{
  myPort = new Serial(this, Serial.list()[4], 9600); //Change this line to the correct serial port
  size(400, 400);
  textFont(createFont("SanSerif", 16));
  myServer = new Server(this, port); // Starts a myServer on port 10002
  background(0);
  println(Serial.list());
}

void mousePressed()
{
  // If the mouse clicked the myServer stops
  myServer.stop();
  myServerRunning = false;
}

void draw()
{
  if (myServerRunning == true)
  {
    
    text("server", 15, 45);
    Client thisClient = myServer.available();
    if (thisClient != null) {
      if (thisClient.available() > 0) {
        background(0);
        text("mesage from: " + thisClient.ip() + " : " + thisClient.readString(), 15, textLine);
        if(toggleOn) toggleOn = false;
        else toggleOn = true;
      }
    }
  } 
  else 
  {
    text("server", 15, 45);
    text("stopped", 15, 65);
  }
  if(toggleOn){
    //myPort.write(65);
  }
  delay(100);
}
