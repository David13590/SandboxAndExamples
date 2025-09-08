#include <ESP32Servo.h>
#include <arduino.h>
#include <wire.h>

//Rover servo pins: yaw 17, grip 23, forwardback 16, pitch 4
//Pitch max 55 ned, 170 max op, ~85 midt
//Yaw max 180 højre, 90 midt, 0 venstre
//grip max 180 åben, MAX 82 lukket
//forwardBack max frem 160, max tilbage 80
Servo myservo;
int pos = 0;
int servoPin = 16;

void setup() {
	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);
	myservo.attach(servoPin, 500, 2400);
	Serial.begin(115200);
}
 
void loop() {
	pos = 80;        
	myservo.write(pos);    // tell servo to go to position in variable 'pos'
	Serial.println(pos);
	delay(3000);  // waits 15ms for the servo to reach the position
	
	pos = 160;
	myservo.write(pos);	 
	Serial.println(pos);
	delay(3000);

	// pos = 0;
	// myservo.write(pos);	 
	// Serial.println(pos);
	// delay(3000);
}