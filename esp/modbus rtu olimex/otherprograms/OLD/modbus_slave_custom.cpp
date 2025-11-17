#include <ModbusMaster.h>
//-------------------
// ModBus Slave
//-------------------

// ================ MODBUS COMMUNICATION CONFIGURATION ================
#define RX_PIN 16           // UART2 RX pin
#define TX_PIN 17            // UART2 TX pin
#define MAX485_DE 21         // RS485 Driver Enable pin
#define MAX485_RE_NEG 19    // RS485 Receiver Enable pin (active low)
#define BAUD_RATE 9600      // Communication speed
#define MODBUS_SLAVE_ID 1   // Slave device address

// ================ DATA BUFFERS ================
uint16_t holdingRegs[2];    // Buffer for holding registers (writable)
uint16_t inputRegs[2];      // Buffer for input registers (read-only)
bool discreteInputs[2];     // Buffer for discrete inputs (binary status)
char frontDoorStatus[10];   // Human-readable front door status
char backDoorStatus[10];    // Human-readable back door status

// Create Modbus master object
ModbusMaster modbus;

// Function to prepare for data transmission
void preTransmission() {
  digitalWrite(MAX485_RE_NEG, HIGH);  // Disable receiver
  digitalWrite(MAX485_DE, HIGH);      // Enable driver
}

// Function to clean up after data transmission
void postTransmission() {
  digitalWrite(MAX485_RE_NEG, LOW);   // Enable receiver
  digitalWrite(MAX485_DE, LOW);       // Disable driver
}

//void getVentSystemMode(){
//    readHoldingRegisters();
//}

void readHoldingRegisters(){
    auto HoldingRegResult = modbus.readHoldingRegisters(0, 1);
    if(0==HoldingRegResult){
        holdingRegs[0] = modbus.getResponseBuffer(0);
        Serial.println(holdingRegs[0]);
    }
    else{
      Serial.print("Could not read Holding register!");
    }
}

void setup() {
  // Initialize RS485 control pins
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_RE_NEG, LOW);
  digitalWrite(MAX485_DE, LOW);

  // Start serial communication for debugging
  Serial.begin(9600);
  Serial.println("ESP32 Modbus RTU Communication Initializing...");

  // Configure UART2 for Modbus communication
  Serial2.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN);

  // Initialize Modbus master with slave ID and UART2
  modbus.begin(MODBUS_SLAVE_ID, Serial2);

  // Set pre- and post-transmission callbacks for RS485 control
  modbus.preTransmission(preTransmission);
  modbus.postTransmission(postTransmission);

  Serial.println("Modbus RTU Communication Initialized Successfully");
  
}

void loop() {
  // Perform Modbus read and write operations
  readHoldingRegisters();
  //writeHoldingRegisters();

  // Add diagnostic separator for readability
  //Serial.println("----------------------------");

  // Delay between communication cycles to prevent overwhelming the bus
  modbus.clearResponseBuffer();
  delay(2000);  // 2-second interval
}
