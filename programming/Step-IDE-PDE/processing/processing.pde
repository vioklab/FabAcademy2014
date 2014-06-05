import processing.serial.*;
Serial myPort;  // The serial port

int mySelectPort = 4;
int portVel = 9600;

int NumOfSerialBytes=3;                              // The size of the buffer array
int[] serialInArray = new int[NumOfSerialBytes];     // Buffer array
int serialCount = 0; 
float m = 0;

void setup() {
  size(300, 600);
//  noLoop();
  // List all the available serial ports
  println(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[mySelectPort], portVel);
  myPort.clear(); 
  myPort.buffer(20);
}

void draw() {
  background(255);
  while (myPort.available () > 0) {
    int inByte = myPort.read();
    if (inByte>255) {
      println(" inByte = "+inByte);    
      exit();
    }
    serialInArray[serialCount] = inByte;
    serialCount++;
    if (serialCount >= NumOfSerialBytes ) {
      serialCount = 0;
    }
    print("Counter: ");
    print("\t");
    print(serialCount);
    print("\t");
    print("Value: ");
    print("\t");
    println(- inByte);

    
  }
  m = map(serialInArray[1] , 7, 200, 0, 200);
  fill(255, 0, 0);
  rect(150, 300, 55, - m);
}

