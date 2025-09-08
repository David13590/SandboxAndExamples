/*#include <Arduino.h>
#include <Wire.h>
#include <ezButton.h>

#define VRX_PIN  34 // ESP32 pin GPIO39 (ADC3) connected to VRX pin
#define VRY_PIN  35 // ESP32 pin GPIO36 (ADC0) connected to VRY pin
#define SW 32 //Button

int valueX = 0; // to store the X-axis value
int valueY = 0; // to store the Y-axis value
bool buttonPush;

void setup() {
  Serial.begin(115200);

  // Set the ADC attenuation to 11 dB (up to ~3.3V input)
  analogSetAttenuation(ADC_11db);
}

void loop() {
  // read X and Y analog values
  valueX = analogRead(VRX_PIN);
  valueY = analogRead(VRY_PIN);
  buttonPush = analogRead(SW);

  // print data to Serial Monitor on Arduino IDE
  Serial.print("x = ");
  Serial.print(valueX);
  Serial.print(", y = ");
  Serial.print(valueY);
  Serial.print(" Button ");
  Serial.println(buttonPush);
  delay(20);
}*/

#include <ezButton.h>
#include <Arduino.h>
#include <Wire.h>

#define VRX_PIN  34 // ESP32 pin GPIO39 (ADC3) connected to VRX pin
#define VRY_PIN  35 // ESP32 pin GPIO36 (ADC0) connected to VRY pin
#define SW_PIN   32 // ESP32 pin GPIO17 connected to SW  pin

ezButton button(SW_PIN);

int valueX0ToNeutral = 0; // to store the X-axis value
int vauleXNeutralToMax = 0;
int neutralLow = 1700;
int neutralHigh = 1900;
int valueX = 0;
int valueY = 0; // to store the Y-axis value
int bValue = 0; // To store value of the button

void setup() {
  Serial.begin(115200);

  // Set the ADC attenuation to 11 dB (up to ~3.3V input)
  analogSetAttenuation(ADC_11db);
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  button.loop(); // MUST call the loop() function first

  // read values
  valueX = analogRead(VRX_PIN);
  valueY = analogRead(VRY_PIN);
  bValue = button.getState();

  Serial.print("x = ");
  Serial.print(valueX);
  Serial.print(", y = ");
  Serial.print(valueY);
  Serial.print(" : button = ");
  Serial.print(bValue);

  int servoValueX = map(valueX, 0, 20, 0, 180);
  int servoValueY = map(valueY, 0, 4095, 0, 180);

  Serial.print(" Servo x = ");
  Serial.print(servoValueX);
  Serial.print(", Servo y = ");
  Serial.println(servoValueY);

}
