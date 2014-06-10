/* User interface - Sending messages from processing to arduino and viceversa. \
    Controlling the RGB led color with UI buttons.
*/
void setup() 
{
  size(200, 150);
  //noloop();
  setupSerial(4);  // Connect to the specified port
  setupUI();      // Setup UI interface
  background(0);
}
 
void draw() {
  _drawUI();
  //_drawBgColor();
}

void keyPressed() {
  sendCMD(key, 100);
}

