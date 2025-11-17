#include <ModbusRTU.h>

#define RXD2 36 // 16
#define TXD2 4 // 15
#define RS485_DIR 14   // DE+RE

//HardwareSerial mySerial(2);
ModbusRTU mb;

void setup() {
  pinMode(RS485_DIR, OUTPUT);
  digitalWrite(RS485_DIR, LOW); 

  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1);

  mb.begin(&Serial2, RS485_DIR);
  mb.slave(1);

  mb.addHreg(0, 1234); 
  mb.addHreg(1, 0);
}

bool coils[20];
u_int16_t regValue;
void loop() {
  if (!mb.slave()) {
    mb.readHreg(1, 0x2012, &regValue);
  }
  while(mb.slave()){
    mb.task();
    delay(10);
  }
  Serial.print(regValue);
  Serial2.print("Hello world");
  delay(500);
}