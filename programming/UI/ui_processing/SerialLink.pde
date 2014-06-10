 import processing.serial.*;

Serial myPort;  // Create object from Serial class
int val;        // Data received from the serial port

void setupSerial(int selectedPort){
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[5].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String[] portsAvailable = Serial.list();           // Get a List of all the serial ports available
  for (int i=0; i <  portsAvailable.length; i++) {   // Iterate over the list and print them on console for selection
    print("[" + i + "]\t");    
    println(portsAvailable[i]);                       
  }
  String portName = portsAvailable[selectedPort];               // "5" is our selection            
  myPort = new Serial(this, portName, 9600);  
}
public void sendCMD(char cmd, int value) { 
  print("SENDING CMD: ");
  print(cmd);
  print(" VALUE: ");
  print(value);
  print(" >> ");
  print(cmd);     
  println(str(value));
  myPort.write(cmd);     
  myPort.write(String.valueOf(value));
  myPort.write('\n');
}
 
void serialEvent(Serial myPort) {
   String myString = myPort.readStringUntil('\n');
    if(myString != null) {
      print("RECEIVD CMD: ");
      println(myString);
    }
}
