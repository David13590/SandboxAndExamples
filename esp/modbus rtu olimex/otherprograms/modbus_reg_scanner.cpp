
// FIX MEE!!! 


for (int addr = 0; addr < 200; addr++) {
  uint8_t result = modbus.readInputRegisters(addr, 1);
  if (result == modbus.ku8MBSuccess) {
    Serial.printf("IR[%d] = %d\n", addr, modbus.getResponseBuffer(0));
  } else {
    Serial.printf("IR[%d] = ERR\n", addr);
  }
  modbus.clearResponseBuffer();
  delay(60);
}
while(true);


for (int addr = 0; addr < 400; addr++) {
  uint8_t result = modbus.readHoldingRegisters(addr, 1);
  if (result == modbus.ku8MBSuccess) {
    Serial.printf("HR[%d] = %d\n", addr, modbus.getResponseBuffer(0));
  } else {
    Serial.printf("HR[%d] = ERR\n", addr);
  }
  modbus.clearResponseBuffer();
  delay(60);
}
while(true);
