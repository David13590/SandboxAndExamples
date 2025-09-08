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

const int neutral = 500;

int minUs = 1000; // Published values for SG90 servos; adjust if needed
int maxUs = 2000;

int angle1;

void setup()
{
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	Serial.begin(9600);
	servoBase.setPeriodHertz(50);      // Standard 50hz servo
	servoLeft.setPeriodHertz(50);      
	servoRight.setPeriodHertz(50);
	servoGripper.setPeriodHertz(50);   
}

void loop() { 
    servoBase.attach(servoBasePin, minUs, maxUs);
	servoLeft.attach(servoLeftPin, minUs, maxUs);
	servoRight.attach(servoRightPin, minUs, maxUs);
	servoGripper.attach(servoGripperPin, minUs, maxUs);
	int xValue = analogRead(joyXPin); // Read X-axis value 
	int yValue = analogRead(joyYPin); // Read Y-axis value 

	// Map joystick values from [0,1023] to [0,180] 
    if (xValue < neutral) {
        angle1 = map(xValue, 0, neutral, 0, 90); 
    }
    else if (xValue > neutral) {
        angle1 = map(xValue, neutral, 1023, 91, 180);
    }
	int angle2 = map(yValue, 0, 1023, 0, 180); 
	// Write mapped values to servos 
	servoBase.write(angle1); 
	servoLeft.write(angle2); 
	delay(15); // Short delay for stability
}