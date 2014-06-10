
int rColor = 100;
int gColor = 100;
int bColor = 100;


void serialSetup(){
}


void checkStimuli() {
  led_RaibowWater(50, 1);
  if (Serial.available()) {
    int valIn = (int)Serial.read();
    //Serial.println(valIn);
    switch(valIn){
      case 0:
        led_RaibowWater(5, 1);
        break;
      case 1:
        led_RaibowWater(50, 1);
        break;
    }
  }
}

