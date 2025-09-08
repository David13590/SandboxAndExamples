#include <Arduino.h>
#include <ESP32Servo.h>

Servo servoBase;
Servo servoLeft;
Servo servoRight;
Servo servoGripper;

const int servoBasePin = 27;
const int servoLeftPin = 26;
const int servoRightPin = 25;
const int servoGripperPin = 14;
const int joyXPin = 34; // X-axis of joystick 
const int joyYPin = 39; // Y-axis of joystick 
const int neutralMin = 1700;
const int neutralMax = 2000;
int minUs = 1000;
int maxUs = 2000;

int angle1;

void setup()
{
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	Serial.begin(115200);
	servoBase.setPeriodHertz(50);
	servoLeft.setPeriodHertz(50);      
	servoRight.setPeriodHertz(50);
	servoGripper.setPeriodHertz(50); 
    servoBase.attach(servoBasePin, minUs, maxUs);
}

void loop() { 
	static int joy1x = 90;
	static int joy1y = 90;
	int joystickXValue = analogRead(joyXPin); // Read X-axis value 
	int joystickYValue = analogRead(joyYPin); // Read Y-axis value 

    if (joystickXValue < neutralMin) {
        if (joy1x < 0) {
        }
        else if (joy1x >= 1) {
            joy1x-=1;
        }
    }
    else if (joystickXValue > neutralMax) {
        if (joy1x > 180) {
        }
        else if (joy1x <= 179) {
            joy1x+=1;
        }
    }
	
	servoBase.write(joy1x); 
	servoLeft.write(joy1y); 
	delay(20);
}