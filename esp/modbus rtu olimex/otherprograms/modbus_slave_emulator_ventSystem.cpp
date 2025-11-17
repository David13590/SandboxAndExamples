/*
ModbusRTU ESP8266/ESP32
Simple slave example

(c)2019 Alexander Emelianov (a.m.emelianov@gmail.com)
https://github.com/emelianov/modbus-esp8266

modified 13 May 2020
by brainelectronics

This code is licensed under the BSD New License. See LICENSE.txt for more info.
*/
#include <Arduino.h>
#include <ModbusRTU.h>
#include "VentSystemRegisters.h"

#define RXD1 3
#define TXD1 1
#define MODBUS_DE GPIO_NUM_21

#define REGN 0x2012
#define SLAVE_ID 1

ModbusRTU mb;

void setup() {
  Serial.begin(9600, SERIAL_8N1, RXD1, TXD1);
  mb.begin(&Serial, MODBUS_DE, true);
  mb.slave(SLAVE_ID);
  
  //Add Registers
  //InputReg
  mb.addIreg(getOutdoorTemp, 8);
  mb.addIreg(runMode, 5);
  mb.addIreg(extractAirTemp, 19);
  mb.addIreg(roomTemp1, 25);
  mb.addIreg(roomTemp2, 31);
  
  //Hreg
  mb.addHreg(fanMode, 3);
  
  //Test Hreg
  mb.addHreg(REGN);
  mb.Hreg(REGN, 130);

  
}

void loop() {
  mb.task();
  yield();
}
