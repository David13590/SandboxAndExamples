#include <arduino.h>
#include "joystick.hpp"

void joystick::setup(int xPin, int yPin, int buttonPin){
    joystick::xPin_private = xPin;
    joystick::yPin_private = yPin;
    joystick::buttonPin_private = buttonPin;
}

joystick::joystickValue& joystick::get_value(){
    //Read joystick value
    int x = analogRead(xPin_private); 
    int y = analogRead(yPin_private);
    int button = digitalRead(buttonPin_private);

    myjoystickvalue.x = x;
    myjoystickvalue.y = y;
    myjoystickvalue.button = button;

    return myjoystickvalue;
}