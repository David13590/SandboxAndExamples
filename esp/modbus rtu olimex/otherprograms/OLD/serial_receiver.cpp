#include <Arduino.h>
// Define TX and RX pins for UART (change if needed)
#define TXD1 4
#define RXD1 36

void setup() {
  Serial.begin(19200);
  Serial2.begin(19200, SERIAL_8N1, RXD1, TXD1);  // UART setup
  
  Serial.println("ESP32 UART Receiver");
}

void loop() {
  // Check if data is available to read
  if (Serial2.available()) {
    // Read data and display it
    String message = Serial2.readStringUntil('\n');
    Serial.println("Received: " + message);
  }
}