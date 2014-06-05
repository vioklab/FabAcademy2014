/*
Title:
Description: . 
Created by: Leonardo Arrata on March - 2014 - BCN, Spain
Created for: Fab Academy - BCN, Spain
Modifications:
  * Leonardo Arrata on March - 2014 - BCN, Spain
The circuit:
  * LED RED attached to pin 7
  * LED GREEN attached to pin 6
  * LED BLUE attached to pin 8
  *  BUTTON attachet to pin 3
 */
 

// VARIABLES
// button
int buttonPin = 3;
int buttonState = 0;
// colors red, green, blue
int ledPins[] = {7,6,8};

// actual Led -> Counter
int xLed = 3; // 3 -> off

void setup(){
  pinMode(buttonPin, INPUT);
}

void loop(){
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    xLed++;
    if(xLed > 3){
      xLed = 0;
    }
    if(xLed == 3){
      fadeOut(xLed);
    }
    fadeIn(xLed);
    fadeOut(xLed-1);
  } else {
    
  }
}

void fadeIn(int ledPin){
   for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPins[ledPin], fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  }
}

void fadeOut(int ledPin){
   for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) {  
    // sets the value (range from 0 to 255):
    analogWrite(ledPins[ledPin], fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  }
}
