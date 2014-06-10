#define LED13 13

String inputString = "";         // a string to hold incoming data
boolean commandComplete = false;  // whether the string is complete

int somethingGlobal = 100;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  pinMode(LED13,OUTPUT);
  ledStripSetup();
}

void loop() {
  // checkCommands and run
  checkCommands();
}


void checkCommands() {
  if (Serial.available()) {
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      commandComplete = true;
    } 
  }

  if (commandComplete) {
    // not really optimize on strings but easier to learn
    // get the first character of the string which is the commands
    char command = inputString.substring(0,1).charAt(0);
    // get the rest of the string which is the integer value
    int value = inputString.substring(1).toInt();
    // clean the string to receive more commands
    inputString = "";
    // set the commands complete to false
    commandComplete = false;
    // execute the received commands with the attached value
    runCommand(command, value);

  }
}

void runCommand(char commands, int value){
  switch (commands) {
  case 'd':   
    Serial.print("COMMAND RED "); 
    Serial.println(value);
    colorWipe(Color(0,200,70), value);
    break;
  case 'r':   
    Serial.print("COMMAND RED "); 
    Serial.println(value);
    colorWipe(Color(255, 0, 0), value);
    break;
  case 'g':
    Serial.print("COMMAND GREEN "); 
    Serial.println(value);
    colorWipe(Color(0, 255, 0), value);
    break;
  case 'b':
    Serial.print("COMMAND BLUE "); 
    Serial.println(value);
    colorWipe(Color(0, 0, 255), value);
    break;
  }
}




