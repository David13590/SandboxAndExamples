
/* #include <Arduino.h>
#include <ModbusMaster.h>
#define SLAVE_ID 1
#define RS485_SERIAL_PORT Serial2
#define RS485_DE_RE_PIN 5 // DE/RE pin for RS485
ModbusMaster mb; // Opret Modbus instans
void setup() {
Serial.begin(115200); // Debug via Serial Monitor
// Start RS485-porten
RS485_SERIAL_PORT.begin(9600, SERIAL_8N1, 16, 17); // RX = 16, TX = 17
// Konfigurer DE/RE pin
pinMode(RS485_DE_RE_PIN, OUTPUT);
// Initialiser Modbus som master
mb.begin(&RS485_SERIAL_PORT, RS485_DE_RE_PIN);
mb.master();
Serial.println(" Modbus RTU master er klar til brug");
}
// Callback efter skriveoperationer
bool cbWrite(Modbus::ResultCode event, uint16_t transactionId, void* data) {
Serial.printf("Skrive-anmodning resultat: 0x%02X, Transaktion: %d\n", event, transactionId);
return true;
}
void loop() {
static uint32_t lastMillis = 0;
if (millis() - lastMillis > 5000) { // Hver 5. sekund
lastMillis = millis();
// Læs coil
uint16_t coilValue;
if (mb.readCoil(SLAVE_ID, 0, &coilValue, 1)) {
Serial.printf("Coil-værdi: %d\n", coilValue);
} else {
Serial.println(" Fejl ved læsning af coil");
}
// Læs holding register
uint16_t regValue;
if (mb.readHreg(SLAVE_ID, 0, &regValue, 1)) {
Serial.printf("Holding register-værdi: %d\n", regValue);
} else {
Serial.println(" Fejl ved læsning af holding register");

4

}
// Skriv til coil
bool newCoilState = !coilValue; // Skift tilstand
if (mb.writeCoil(SLAVE_ID, 0, newCoilState, cbWrite)) {
Serial.printf(" Coil-skrivning sendt: %d\n", newCoilState);
} else {
Serial.println(" Fejl ved afsendelse af coil-skrivning");
}
// Skriv til holding register
uint16_t newRegValue = random(0, 100);
if (mb.writeHreg(SLAVE_ID, 0, newRegValue, cbWrite)) {
Serial.printf(" Skrivning til holding register sendt: %d\n", newRegValue);
} else {
Serial.println(" Fejl ved afsendelse af register-skrivning");
}
}
// Kald Modbus-håndtering
mb.task();
yield();
} */