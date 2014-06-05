#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs_2_3 = CapacitiveSensor(2,3);        // 10M resistor between pins 2 & 3, pin 3 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_2_4 = CapacitiveSensor(2,4);        // 10M resistor between pins 2 & 4, pin 4 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_2_5 = CapacitiveSensor(2,5);        // 10M resistor between pins 2 & 5, pin 5 is sensor pin, add a wire and or foil

void setup()                    
{
   cs_2_3.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   cs_2_4.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   cs_2_5.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_2_3.capacitiveSensor(30);
    long total2 =  cs_2_4.capacitiveSensor(30);
    long total3 =  cs_2_5.capacitiveSensor(30);
    
//    Serial.print("SENSOR 1");  
//    Serial.print("\t");  
//    Serial.print(millis() - start);        
//    Serial.print("\t");                   
//    Serial.println(total1);
    
//    Serial.print("SENSOR 2");  
//    Serial.print("\t");  
//    Serial.print(millis() - start);        
//    Serial.print("\t");                   
//    Serial.println(total2);
//    
//    Serial.print("SENSOR 3");  
//    Serial.print("\t");  
//    Serial.print(millis() - start);        
//    Serial.print("\t");                   
//    Serial.println(total3);
    
    //Serial.write(total1);
Serial.write(total2);
//    Serial.write(byte(total2));
    
    
    delay(10);                             // arbitrary delay to limit data to serial port 
}
