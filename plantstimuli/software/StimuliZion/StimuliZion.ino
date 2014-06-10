
#include "SPI.h" // LCD library
#include "Adafruit_WS2801.h" // LED strip library

// Choose which 2 pins you will use for output.
uint8_t dataPin  = 2;    // Yellow wire on Adafruit Pixels
uint8_t clockPin = 3;    // Green wire on Adafruit Pixels

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(16, dataPin, clockPin);


void setup() {
  /* SERIAL & I2C Communication - MASTER READER */
  Serial.begin(9600);
  serialSetup();
  // important! 
  
  /* LCD CRYSTAL DISPLAY */
  //lcd.begin(16, 2);
  //lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print("Hello");

  /* LED STRIP */
  // Update LED contents, to start they are all 'off'
  strip.begin();
  strip.show();
  //led_PotController();
}


void loop() {
  //Serial.println(time);
  // wait a second so as not to send massive amounts of data
  //delay(1000);
   //led_PotController();
   checkStimuli();
  // led_RaibowWater(10,1);
   
/* SERIAL CONTROLLER */
  if (Serial.available() > 0) {
    // lee el byte entrante:
    char serialRun = Serial.read();
    switch(serialRun){
    case '1':
      led_PotController();
      Serial.println("Led Status 1");
      break;
    case '2':
      led_RaibowWater(10,1);
      Serial.println("Led Status 2");
      break;
    }
  } 
  else {
    //led_RaibowWater(10,1);
    //led_PotController();

  }
 
}





