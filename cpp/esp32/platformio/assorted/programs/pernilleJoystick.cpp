#include <Arduino.h>
#include <Wire.h>
// //JoystickLeft
// #define JOY_LEFT_VRX_PIN 39
// #define JOY_LEFT_VRY_PIN 36
// #define JOY_LEFT_SW_PIN 17

// //JoystickRight
// #define JOY_RIGHT_VRX_PIN 33
// #define JOY_RIGHT_VRY_PIN 32
// #define JOY_RIGHT_SW_PIN 37

// #define pcbButtonLeft 2
// #define pcbButtonRight 38


// Joystick 1
#define VRX_PIN 39
#define VRY_PIN 36
#define SW_PIN  17

// Joystick 2
#define VRX_PIN2 33
#define VRY_PIN2 32

#define LEFT_THRESHOLD  1000
#define RIGHT_THRESHOLD 3000
#define UP_THRESHOLD    1000
#define DOWN_THRESHOLD  3000

#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

// Joystick 1
int valueX = 0;
int valueY = 0;
int buttonState = 0;
int command = COMMAND_NO;

// Joystick 2
int valueX2 = 0;
int valueY2 = 0;

void printJoystickState(int x, int y, const char* joystickName);

void setup() {
  Serial.begin(115200);
  pinMode(SW_PIN, INPUT_PULLUP);
  Serial.println("Setup complete");
}

void loop() {
  // Read values from both joysticks
  valueX = analogRead(VRX_PIN);
  valueY = analogRead(VRY_PIN);
  valueX2 = analogRead(VRX_PIN2);
  valueY2 = analogRead(VRY_PIN2);
  buttonState = digitalRead(SW_PIN);

  // Debugging: Print raw values
  Serial.print("Joystick 1: ");
  Serial.print("X: ");
  Serial.print(valueX);
  Serial.print(", Y: ");
  Serial.print(valueY);

  Serial.print("Joystick 2: ");
  Serial.print("X: ");
  Serial.print(valueX2);
  Serial.print(", Y: ");
  Serial.print(valueY2);

  // Print states for both joysticks
  printJoystickState(valueX, valueY, "Joystick 1");
  printJoystickState(valueX2, valueY2, "Joystick 2");

  delay(1);
}

void printJoystickState(int x, int y, const char* joystickName) {
  Serial.print(joystickName);
  Serial.print(": ");

  if (x < LEFT_THRESHOLD)
    Serial.print("Left ");
  else if (x > RIGHT_THRESHOLD)
    Serial.print("Right ");

  if (y < UP_THRESHOLD)
    Serial.print("Up ");
  else if (y > DOWN_THRESHOLD)
    Serial.print("Down ");

  if (x >= LEFT_THRESHOLD && x <= RIGHT_THRESHOLD && y >= UP_THRESHOLD && y <= DOWN_THRESHOLD) {
    Serial.print("Not moving ");
  }

  Serial.println();
}