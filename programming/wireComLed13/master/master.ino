// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop()
{
  requestSlave();
  
}

void requestSlave(){
  Wire.requestFrom(2, 1);    // request 6 bytes from slave device #2
  while(0 < Wire.available())    // slave may send less than requested
  { 
    char c = Wire.read(); // receive a byte as character
    runSlaveCommand(c);
    masterWrite(2, 'A');
    delay(1500);
  }
}

void runSlaveCommand(char command){
  switch (command) {
  case 'A':   // means are connected
    Serial.print("Master/Reques - Slave/SenderSND - NEQUEST COMMAND: ");
    Serial.print("\t");
    Serial.println(command);
    digitalWrite(13,HIGH);
    delay(1500);
    break;
  case 'B':   
    Serial.print("COMMAND: ");
   Serial.print("\t");
    Serial.println(command);
    run13Led(500);
    break;
  }
}

void run13Led(int value){
  digitalWrite(13,HIGH);
  delay(value);
  digitalWrite(13,LOW);
  delay(value);
}


void masterWrite(int device, char command){
  Wire.beginTransmission(device); // transmit to device
  Wire.write('A');              // sends one byte  
  Wire.endTransmission();    // stop transmitting
// Serial.println('SENT A');
}
