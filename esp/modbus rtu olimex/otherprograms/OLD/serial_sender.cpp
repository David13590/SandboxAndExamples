#include <Arduino.h>
// Define TX and RX pins for UART (change if needed)
#define TXD1 17
#define RXD1 16

// Use Serial1 for UART communication
HardwareSerial mySerial(1);

int counter = 0;

void setup() {
  Serial.begin(19200);
  mySerial.begin(19200, SERIAL_8N1, RXD1, TXD1);  // UART setup
  
  Serial.println("ESP32 UART Transmitter");
}

void loop() {
  
  // Send message over UART
  mySerial.println(String(counter));
  
  Serial.println("Sent: " + String(counter));
  
  // increment the counter
  counter++;
  
  delay(1000); 
}