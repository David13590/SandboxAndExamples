#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

volatile byte dataReceived = 0;

void setup() {
  SPI.begin(); // Initialize as SPI Slave
  SPI.onData([](byte data) {
    dataReceived = data; // Store received data
    Serial.printf("Received: 0x%02X\n", dataReceived);
  });
  Serial.begin(115200);
}

void loop() {
  // Continuously monitor the received data
  delay(100);
}