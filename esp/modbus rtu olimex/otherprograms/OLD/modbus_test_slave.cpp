#include <ModbusRTU.h>

#define RXD2 16
#define TXD2 17
#define RS485_DIR 22

HardwareSerial RS485(2);
ModbusRTU mb;

void setup() {
  pinMode(RS485_DIR, OUTPUT);
  digitalWrite(RS485_DIR, LOW);

  Serial.begin(115200);
  RS485.begin(9600, SERIAL_8N1, RXD2, TXD2);

  mb.begin(&RS485, RS485_DIR);
  mb.slave(1);

  mb.addHreg(0, 1234);
  mb.addHreg(1, 0);
}

void loop() {
  static uint32_t last = 0;
  if (millis() - last > 1000) {
    last = millis();
    mb.Hreg(1, mb.Hreg(1) + 1);
  }

  mb.task();
  yield();
}