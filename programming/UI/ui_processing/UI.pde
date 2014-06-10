import controlP5.*;

ControlP5 cp5;
int myColor = color(10,200,70);
int c1, c2;
float n, n1;

Slider abc;

void setupUI() {
  noStroke();
  // control P5 create object
  cp5 = new ControlP5(this);
  // create array of  buttons
  String[] actionsArray = {"DEFAULT","RED","GREEN","BLUE"};
  // navigate throw array
  for(int i=0; i < actionsArray.length;i++){
  // create the button
  cp5.addButton(actionsArray[i])
    .setValue(i)
      .setPosition(10, 20*i+10)
        .setSize(100, 19)
          ;
  }
}

void _drawUI() {
  background(myColor);
  myColor = lerpColor(c1, c2, n);
  n += (1-n)* 0.1;
}

public void controlEvent(ControlEvent theEvent) {
  String eventName = theEvent.getController().getName();
  if(eventName == "DEFAULT"){
     sendCMD('d', 20);
     c2 = color(10,200,70);
  }
  if(eventName == "RED"){
     sendCMD('r', 50);
     c2 = color(255, 0, 0);
  }
  if(eventName == "GREEN"){
     sendCMD('g', 50);
     c2 = color(0, 255, 0);
  }
  if(eventName == "BLUE"){
     sendCMD('b', 50);
     c2 = color(0, 0,255);
  }
   c1 = c2;
//  if( theEvent.getController().getValue == 1) {
//    println(theEvent.getController().getValue);  // Does not execute
//  }
 //theEvent.getController().getName()
    
  n = 0;
}


