#include <Arduino.h>
/*
  ModbusRTU ESP8266/ESP32
  Simple slave example

  (c)2019 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266

  modified 13 May 2020
  by brainelectronics

  This code is licensed under the BSD New License. See LICENSE.txt for more info.
*/
#define RXD1 36 // 16
#define TXD1 4 // 15
#define MODBUS_DE GPIO_NUM_14

#include <ModbusRTU.h>

#define SLAVE_ID 1
#define SLAVE_ID2 2
#define REGN  19
ModbusRTU mb;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1);
  mb.begin(&Serial1, TXD1, true);
  mb.client();
  gpio_set_direction(MODBUS_DE, GPIO_MODE_OUTPUT);
}

const uint16_t REG = REGN; // Modbus Hreg Offset
uint16_t result = 0;
uint16_t result2 = 0;
uint32_t showLast = 0;

void loop() {
  auto error = mb.readHreg(SLAVE_ID, REG, &result);  // Initiate Read Hreg from Modbus Slave
  //auto error2 = mb.readHreg(SLAVE_ID2, REG, &result2);

  unsigned int count = 0;
  while(mb.slave()) { // Check if transaction is active
      mb.task();
      delay(20);
      count++;
    }
    Serial.println();

  mb.task();
  if(count < 100)
  { 
    Serial.println("Value: " + result);
    
    //Serial.println("Value: " + result2);
  } else 
  {
    Serial.print(". ");
    //Serial.println("Result: " + result);
    //Serial.println("Result2: " + result2);
  }
  Serial.println();
  delay(2000);
}
