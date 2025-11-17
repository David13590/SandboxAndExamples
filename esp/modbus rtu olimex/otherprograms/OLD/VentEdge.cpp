#include <ModbusMaster.h>

// ================ MODBUS COMMUNICATION CONFIGURATION ================
#define RX_PIN 36           // UART2 RX pin
#define TX_PIN 4            // UART2 TX pin
#define MAX485_DE 5         // RS485 Driver Enable pin
#define MAX485_RE_NEG 14    // RS485 Receiver Enable pin (active low)
#define BAUD_RATE 9600      // Communication speed
#define MODBUS_SLAVE_ID 1   // Slave device address

// ================ DATA BUFFERS ================
uint16_t holdingRegs[2];
uint16_t inputRegs[9];  // Udvid til at rumme alle registre (0-8)

ModbusMaster modbus;

// ================ RS485 Direction Control ================
void preTransmission() {
  digitalWrite(MAX485_RE_NEG, HIGH);  // Disable receiver
  digitalWrite(MAX485_DE, HIGH);      // Enable driver
}

void postTransmission() {
  digitalWrite(MAX485_RE_NEG, LOW);   // Enable receiver
  digitalWrite(MAX485_DE, LOW);       // Disable driver
}

void setup() {
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_RE_NEG, LOW);
  digitalWrite(MAX485_DE, LOW);
  
  Serial.begin(115200);
  Serial.println("ESP32 Modbus RTU Communication Initializing...");
  
  Serial2.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN);
  modbus.begin(MODBUS_SLAVE_ID, Serial2);
  modbus.preTransmission(preTransmission);
  modbus.postTransmission(postTransmission);
  
  Serial.println("Modbus RTU Communication Initialized Successfully");
}

// =============== WRITE FAN MODE ===============
// Fan Mode Control (Holding Register 367)
// 0 = Off
// 1 = Manual Reduced
// 2 = Manual Normal
// 3 = Auto Speed
void writeFanMode(uint16_t mode) {
  unsigned long startTime = millis();
  uint8_t result = modbus.writeSingleRegister(367, mode);
  unsigned long duration = millis() - startTime;
  
  if (result == modbus.ku8MBSuccess) {
    Serial.printf("SUCCESS: FanMode=%u written to Reg[367]. Time=%lums\n",
                  mode, duration);
  } else {
    Serial.printf("ERROR writing FanMode=%u to Reg[367] (code %u). Time=%lums\n",
                  mode, result, duration);
  }
}

// =============== READ INPUT REGISTERS ===============
void readInputRegisters() {
  unsigned long startTime = millis();
  
  // Læs register 0 (Outdoor temperature - reg 533)
  uint8_t result = modbus.readInputRegisters(0, 1);
  if (result == modbus.ku8MBSuccess) {
    inputRegs[0] = modbus.getResponseBuffer(0);
    float outdoorTemp = inputRegs[0] / 10.0f;
    Serial.printf("Input Reg[0] (533) = %u (Outdoor Temp: %.1f °C)\n",
                  inputRegs[0], outdoorTemp);
  } else {
    Serial.printf("Read Input Reg[0] Error (code %u)\n", result);
  }
  
  delay(100);  // Kort pause mellem læsninger
  
  // Læs register 6-8 i én operation (Supply air, Setpoint, Extract air)
  result = modbus.readInputRegisters(6, 3);
  unsigned long duration = millis() - startTime;
  
  if (result == modbus.ku8MBSuccess) {
    inputRegs[6] = modbus.getResponseBuffer(0);
    inputRegs[7] = modbus.getResponseBuffer(1);
    inputRegs[8] = modbus.getResponseBuffer(2);
    
    float supplyTemp = inputRegs[6] / 10.0f;
    float setpointTemp = inputRegs[7] / 10.0f;
    float extractTemp = inputRegs[8] / 10.0f;
    
    Serial.printf("Input Reg[6] (539) = %u (Supply Air Temp: %.1f °C)\n",
                  inputRegs[6], supplyTemp);
    Serial.printf("Input Reg[7] (540) = %u (Setpoint Temp: %.1f °C)\n",
                  inputRegs[7], setpointTemp);
    Serial.printf("Input Reg[8] (541) = %u (Extract Air Temp: %.1f °C)\n",
                  inputRegs[8], extractTemp);
  } else {
    Serial.printf("Read Input Reg[6-8] Error (code %u)\n", result);
  }
  
  Serial.printf("Total Read Time: %lums\n", duration);
}

// =============== LOOP ===============
void loop() {
  // Step 1: Set fanmode to Manual Reduced (1)
  writeFanMode(1);
  
  // Step 2: Allow system to react
  delay(300);
  
  // Step 3: Read all temperature registers
  readInputRegisters();
  
  Serial.println("----------------------------");
  delay(2000);
}
