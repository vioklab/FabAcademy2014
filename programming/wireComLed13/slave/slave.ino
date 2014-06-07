// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent);
  pinMode(13,OUTPUT); 
  //Serial.begin(9600);
}

void loop()
{
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
    Wire.write("A"); // send 1 byte -> A means conected
    digitalWrite(13,HIGH);      
}
void startLedPlay()
{
    Wire.write("B"); // send 1 byte -> B means start    
}

void receiveEvent(int howMany)
{
  while(0 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.println(c);
    switch (c){
       case 'A':
           run13Led(2000);
           Wire.onRequest(startLedPlay);
           delay(500);
           break; 
    }
  }
}
  

void run13Led(int value){
  digitalWrite(13,HIGH);
  delay(value);
  digitalWrite(13,LOW);
  delay(value);
}

