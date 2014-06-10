controlP5.Slider ui_slider;

class UIsense {
  int value, x =20;

  UIsense(String thePrefix, int thePosY) {
    ui_slider = cp5.addSlider( "value-"+thePrefix ).setRange( 0, 255 ).setPosition(x, thePosY).plugTo( this, "setValue" ).setValue(127).setLabel(thePrefix);
    // description : round turning dial knob
    // parameters  : name, minimum, maximum, default value (float, x, y, diameter
    
}
  void setValue(int theValue) {
    value = theValue;
  }
  
  void hideUI(){
    //ui_slider.hide();
    ui_slider.setValue(20);
    //ui_slider.setPosition(-100, 40);
  }
  void showUI(){
    //ui_slider.show();
    ui_slider.setPosition(20, 40);
  }

  
}

