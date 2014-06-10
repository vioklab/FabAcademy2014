

byte cR = 0;
byte cG = 0;
byte cB = 0;


byte mainColor = 0;

byte colorPallete[6][3]={
  {
    0,200,70     }
  , // SHINY GREEN -> MAIN COLOR
  {
    0,255,0     }
  , // PURE GREEN
  {
    0,0,255     }
  , // PURE BLUE
  {
    0,255,255     }
  , // SHINY BLUE - 1 
  {
    255,0,0     }
  , // PURE RED
  {
    180,255,0     }
  , // YELLOW
};


/* --------------------------------------------------  */
/* CONTROLLERS */
/* --------------------------------------------------  */
/* LED POT CONTROLLER */

int ledR,ledG,ledB;
int potValue = 0, potValueMap = 0;

void rLED(int R){
   for (int i=0; i < strip.numPixels(); i++) {
    ledR = R;
    ledG = 0;
    ledB = 0;

    strip.setPixelColor(i, ledR , ledG, ledB);
  }
  strip.show();
}

void led_PotController(){
  potValue = analogRead(A0);
  potValueMap = constrain(map(potValue, 13, 1006, 0, 255),0,255);

  for (int i=0; i < strip.numPixels(); i++) {
    ledR = 0;
    ledG = 255-potValueMap;
    ledB = potValueMap;

    strip.setPixelColor(i, ledR , ledG, ledB);
  }
  strip.show();

  //    Serial.print("R: ");
  //    Serial.print("\t");
  //    Serial.print(ledR);
  //    Serial.print("\t");
  //    
  //    Serial.print("G: ");
  //    Serial.print("\t");
  //    Serial.print(ledG);
  //    Serial.print("\t");
  //    
  //    Serial.print("B: ");
  //    Serial.print("\t");
  //    Serial.println(ledB);
  //    Serial.println("----------------------------------------- ");
}

/* RAINBOW WATTER EFFECT CONTROLLER */
void led_RaibowWater(uint8_t wait, int type) {
  int i, j;
  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      switch(type){
      case 1:
        strip.setPixelColor(i, Wheel_Water( j));
        break;
      }
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}
// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;
  
  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}
/* WHEEL */
uint32_t Wheel_Water(byte WheelPos)
{
  if (WheelPos < 85) {
    // turn color to (0,0,255);
    return Color(0, 255 - WheelPos * 3, WheelPos * 3);
  } 
  else if (WheelPos < 170) {
    WheelPos -= 85;
    // turn color to (0,255,0);
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } 
  else {
    // turn color to (0,255,0); FFIXED VALUE
    WheelPos -= 170; 
    return Color(0,  255, 0);
  }
}


/* --------------------------------------------------  */
/* Helper functions */
/* --------------------------------------------------  */
// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

/* WHEELS */
//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
    return Color(0, 255, 255);
  } 
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return Color(0, WheelPos * 3 , 255 - WheelPos * 3);
  } 
  else {
    WheelPos -= 170; 
    return Color(0, 0, WheelPos * 3);
  }
}







