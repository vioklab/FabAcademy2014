import controlP5.*;
import oscP5.*; // -->se importan las librerías oscP5 y netP5
import netP5.*;

ControlP5 cp5;
UIsense UI_x, UI_y;
controlP5.Knob ui_knob, ui_knob_2;
OscP5 oscP5; //--> definición del objeto
NetAddress direccionRemota;



int puerto;
String ip;

float cX=0, cY=0, mX=0, mY=0;
float cMax = 0;


String[] gestures = {
  "nothing", "oneThumb", "TwoThumb", "Grab"
};
color[] colors = {
  color(255, 255, 255), color(0, 255, 215)
};
color background = color(0, 35, 50);

float[][] gesturesMaxMap = new float[gestures.length][2];


void setup() {
  PortSelected=4;
  PortSelectedController=6;
  
  size(1000, 1000);
  cp5 = new ControlP5(this); 
  ui_knob = cp5.addKnob("graphXspacer", 0.0, 10.0, 5.0, 20, 10, 50);

  for (int i = 0; i<gestures.length;i++) {
    cp5.addButton(gestures[i])
      .setPosition(10, (i*30)+90)
        .setSize(80, 20)
          ;
  }


  noLoop();
  
  /* ==================================================================== */
  SerialPortSetup();      // speed of 9600 bps etc.
  //SerialControllerSetup(); // speed of 9600 bps etc.
  /* ==================================================================== */
  /* OSCp5 */
  ip = "127.0.0.1"; //-->dirección ip a donde se envían los mensajes (en este caso localhost)
  puerto = 11112;
  oscP5 = new OscP5(this, puerto); //-->inicialización del objeto
  direccionRemota = new NetAddress(ip, puerto); //-->Entrada: mensajes de entrada por el puerto especificado
}


void draw() {

  background(background);
  OscMessage mesageTouch = new OscMessage("/touch/gesture");
  /* ====================================================================
   Print the graph
   ====================================================================  */
  
  if ( DataRecieved3 ) {

    pushMatrix();
    pushStyle();
    // filter to find Current x and y max value
    mY=0;
    mX=0;
    for (int i=0; i< Time3.length; i++) {
      cX = i;
      cY = Voltage3[i];    
      if (mY < Voltage3[i])
      {
        mX = cX;
        mY = cY;
        
      }
      textSize(9);

      fill(colors[1]);
      rect(cX*ui_knob.value() + 150, 0, 1, cY-5);
      ellipse(cX*ui_knob.value() + 150, cY, 3, 3);
      text(i, cX*ui_knob.value() + 150, cY+10);

      fill(colors[0]);
      text(mY, mX*ui_knob.value()+110, mY);
      ellipse(mX*ui_knob.value() + 150, mY, 5, 5);
      noStroke();
      rect(mX*ui_knob.value() + 150, 0, 1, mY);
    }
    popStyle();
    popMatrix();

    //    
    //    println("=======================================================");
    //   // ui_knob.setValue(int (Time3));
    //    //ui_knob_2.setValue(int (max(Voltage3)));
    ////    print("/t");
    ////    print("Time3");
    ////    print(Time3);
    ////    print("/t");
    ////    print("Voltage3:");
    ////    println(Voltage3);
    //    

    //
    float gestureOneDiff =0;
    float gestureTwoDiff =0;
    float gestureThreeDiff =0;
    //
    //    /* ====================================================================
    //     Gesture compare
    //     ====================================================================  */
    float totalDist = 0;
    int currentMax = 0;
    float currentMaxValue = -1;
    for (int i = 0; i < 4;i++)
    {
//if (mousePressed && mouseX > 750 && mouseX<800 && mouseY > 100*(i+1) && mouseY < 100*(i+1) + 50)
//{
//        fill(255, 0, 0);
//        gesturePoints[i][0] = Time3[MyArduinoGraph.maxI];
//        gesturePoints[i][1] = Voltage3[MyArduinoGraph.maxI];
//        gesturePoints[i][0] = mX;
//        gesturePoints[i][1] = mY;
//
//text(gesturePoints[i][0],mX+100,mY);
//        text(gesturePoints[i][1],mX+100,mY+20);
//
//}  
// else
//{
//        fill(0, 0, 100);
//        text(gesturePoints[0][0], mX+100, mY);
//        text(gesturePoints[1][1], mX+100, mY+20);
// }

      // HOW CALCULATE DE GESTURE BY DISTANCE
      //calucalte individual dist
      gestureDist[i] = dist(Time3[MyArduinoGraph.maxI], Voltage3[MyArduinoGraph.maxI], gesturePoints[i][0], gesturePoints[i][1]);
      
      totalDist = totalDist + gestureDist[i];
      //      
      // -> OSC Touch Message
      mesageTouch.add(Time3[MyArduinoGraph.maxI]);
      mesageTouch.add(Voltage3[MyArduinoGraph.maxI]);
      mesageTouch.add(gestureDist[i]);
      mesageTouch.add(gesturePoints[i][0]);
      mesageTouch.add(gesturePoints[i][1]);
      //        
      ////      println( "Time3[MyArduinoGraph.maxI]: "+Time3[MyArduinoGraph.maxI]+
      ////               " | Voltage3[MyArduinoGraph.maxI]: "+Voltage3[MyArduinoGraph.maxI]+
      ////               " | gestureDist["+i+"]: "+gestureDist[i]+
      ////               " | gesturePoints[0]: "+gesturePoints[i][0]+
      ////               " | gesturePoints[1]: "+gesturePoints[i][1]
      ////               );
      //
      if (gestureDist[i] < currentMaxValue || i == 0)
      {
        currentMax = i;
        currentMaxValue =  gestureDist[i];
        // -> OSC Touch Message
        mesageTouch.add(currentMax);
        mesageTouch.add(currentMaxValue);
        
      }
    }
    
    totalDist=totalDist /4;
    // -> OSC Touch Message
    // Set the geture
    mesageTouch.add(totalDist);
    for (int i = 0; i < 4 ;i++)
    {
      float currentAmmount = 0;
      currentAmmount = 1-gestureDist[i]/totalDist;
      if (currentMax == i)
      {
        fill(0, 0, 0);
        //text(names[i],50,450); // xxxx
        fill(currentAmmount*255.0f, 0, 0);
      }
      else
      {
        fill(255, 255, 255);
      }

 //PRINT THE SQUARES BUTTONS (TAKE OUT)
//stroke(0, 0, 0);
//rect(750, 100 * (i+1), 50, 50);
//
//
//      fill(255, 0, 0);
//      rect(800, 100* (i+1), max(0, currentAmmount*50), 50);
//      println("-------------");
      
      //      //println("TOTAL DIST: "+totalDist+" | currentMax:"+currentMax+ " | currentMaxValue: "+currentMaxValue);
    }

    // -> SEND OSC Touch Message
    //println( "gesture"++"totalDist:"+totalDist+" | currentMax: "+currentMax+" | currentMaxValue: "+currentMaxValue);
    oscP5.send(mesageTouch, direccionRemota);
    print("CurrentMax: ");
    print(currentMax);
    print("/t CurrentMaxValue: ");
    println(currentMaxValue);
    
    
    
    for (int index = 0; index<gestures.length; index++) {
      
      
      // DEBUGGING
      print("gesturesMaxMap["+index+"][0] mX:");
      print(gesturesMaxMap[index][0]);
      print("\t gesturesMaxMap["+index+"][1] mY:");
      println(gesturesMaxMap[index][1]);

      stroke(0);
      if (index > 0) {
        fill(255, 255, 255);
        noStroke();
        rect(gesturesMaxMap[index][0]*ui_knob.value() + 147, 0, 3, gesturesMaxMap[index][1]);
        textSize(9);
        text(gestures[index], gesturesMaxMap[index][0]*ui_knob.value() + 150, gesturesMaxMap[index][1]+20.0);
        line(gesturesMaxMap[index-1][0]*ui_knob.value() + 147, gesturesMaxMap[index-1][1], gesturesMaxMap[index][0]*ui_knob.value() + 147, gesturesMaxMap[index][1]);
      }
      
    }
  }
}

void stop()
{
  myPort.stop();
  super.stop();
}

void controlEvent(ControlEvent theEvent) {
  //print(theEvent.controller().name());
  //println(", value : "+theEvent.controller().value());
  if (theEvent.controller().name()=="graphXspacer") {
    //println(", value : "+theEvent.controller().value());
  }
  for (int index = 0; index<4; index++) {
    if (theEvent.controller().name()==gestures[index]) {
      
        gesturePoints[index][0] = Time3[MyArduinoGraph.maxI];
        gesturePoints[index][1] = Voltage3[MyArduinoGraph.maxI];
        gesturePoints[index][0] = mX;
        gesturePoints[index][1] = mY;
        
        gesturesMaxMap[index][0] = mX;
        gesturesMaxMap[index][1] = mY;

      sendCMD(index);
      print("INDEX:"+index);

    }
  }
}

