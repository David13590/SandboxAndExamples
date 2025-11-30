#include <Arduino.h>
// Hardware Serial 2 pins
#define RXD2 16
#define TXD2 17


void setup() {
  
  // Initialize serial
  Serial.begin(9600);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);    //Hardware Serial of ESP32

}

void loop() {

  // Serial 2 available
  if (Serial2.available())
  {
   
  // Do something
    serial.print("hello")
  }
}