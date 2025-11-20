#include <ModbusMaster.h>
#include "VentSystemRegisters.hpp"

// ================ MODBUS COMMUNICATION CONFIGURATION ================
#define RX_PIN 36           // UART2 RX pin
#define TX_PIN 4            // UART2 TX pin
#define MAX485_DE 5         // RS485 Driver Enable pin
#define MAX485_RE_NEG 14    // RS485 Receiver Enable pin (active low)
#define BAUD_RATE 9600      // Communication speed
#define MODBUS_SLAVE_ID 1   // Slave device address
#define MODBUS_SLAVE_ID2 2

// ================ DATA BUFFERS ================
const int sizeOfInputRegisterBuffer = sizeof(inputRegisterList)/sizeof(inputRegisterList[0]); // Get size of inputRegisterList
const int sizeOfHoldingRegisterBuffer = sizeof(holdingRegisterList)/sizeof(holdingRegisterList[0]);
uint16_t holdingRegsBuffer[sizeOfHoldingRegisterBuffer];  // Buffer for holding registers (writable)
uint16_t inputRegsBuffer[sizeOfInputRegisterBuffer];      // Buffer for input registers (read-only)
bool discreteInputsBuffer[2];     // Buffer for discrete inputs (binary status)

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

void readHoldingRegisters(int hRegToRead, int hRegBufferNumber){
    auto HoldingRegResult = modbus.readHoldingRegisters(hRegToRead, 1);
    if(0==HoldingRegResult){
        holdingRegsBuffer[hRegBufferNumber] = modbus.getResponseBuffer(1)<<8; // Bit shift 8-bit response buffer 8 left creating a 16-bit int.
        holdingRegsBuffer[hRegBufferNumber] += modbus.getResponseBuffer(0);   // 
    }
    else{
      Serial.println("Error reading: Holding register");
    }
}

void readInputRegisters(int iRegToRead, int iRegBufferNumber){
  auto InputRegResult = modbus.readInputRegisters(iRegToRead, 1);
  if(0==InputRegResult){
        inputRegsBuffer[iRegBufferNumber] = modbus.getResponseBuffer(1)<<8;
        inputRegsBuffer[iRegBufferNumber] += modbus.getResponseBuffer(0);
    }
    else{
      Serial.println("Error reading: Input register");
    }
}

String airUnitRunModeString(int inputRegisterRunMode){
  String caseReturn = "";
  switch (inputRegisterRunMode){
    case 0: caseReturn = "Stopped"; break;
    case 1: caseReturn = "Starting up"; break;
    case 2: caseReturn = "Starting reduced Speed"; break;
    case 3: caseReturn = "Starting full speed"; break;
    case 4: caseReturn = "Starting normal run"; break;
    case 5: caseReturn = "Normal run"; break;
    case 6: caseReturn = "Support control heating"; break;
    case 7: caseReturn = "Support control cooling"; break;
    case 8: caseReturn = "CO2 run"; break;
    case 9: caseReturn = "Night cooling"; break;
    case 10: caseReturn = "Full speed stop"; break;
    case 11: caseReturn = "Stopping fan"; break;
  };
  return caseReturn;
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
  readInputRegisters(inputRegisterList[0].reg.modbusAddress, 0);
  readInputRegisters(inputRegisterList[1].reg.modbusAddress, 1);
  readInputRegisters(inputRegisterList[2].reg.modbusAddress, 2);
  readInputRegisters(inputRegisterList[3].reg.modbusAddress, 3);
  readInputRegisters(inputRegisterList[4].reg.modbusAddress, 4);

  readHoldingRegisters(holdingRegisterList[0].reg.modbusAddress, 0);
  
  for(int inputRegisterEntries = 0; inputRegisterEntries < sizeOfInputRegisterBuffer; inputRegisterEntries++){
    // if(inputRegisterEntries == 0){
    //   delay(20);
    //   Serial.println("OutdoorTemp: " + inputRegsBuffer[inputRegisterEntries]);
    // }  
    // else if(inputRegisterEntries == 1){
    //   delay(20);
    //   Serial.println("RunMode: " + inputRegsBuffer[inputRegisterEntries] + airUnitRunModeString(inputRegsBuffer[inputRegisterEntries]));
    // }
    // else if(inputRegisterEntries == 2){
    //   delay(20);
    //   Serial.println("extractedAirTemp: " + inputRegsBuffer[inputRegisterEntries]);
    // }
    // else if(inputRegisterEntries == 3){
    //   delay(20);
    //   Serial.println("roomTemp1: " + inputRegsBuffer[inputRegisterEntries]);
    // }
    // else if(inputRegisterEntries == 4){
    //   delay(20);
    //   Serial.println("roomTemp2: " + inputRegsBuffer[inputRegisterEntries]);
    // }
    // else{
    //   delay(20);
    //   Serial.println(inputRegsBuffer[inputRegisterEntries]);
    // }
        
  
    if(0==inputRegisterEntries){
      Serial.print("OutdoorTemp: ");
      Serial.print(inputRegsBuffer[inputRegisterEntries]);
      Serial.println("°C");
    }
    if(1==inputRegisterEntries){
      Serial.print("Runmode: ");
      Serial.print(inputRegsBuffer[inputRegisterEntries]);
      Serial.print(" ");
      Serial.println(airUnitRunModeString(inputRegsBuffer[inputRegisterEntries]));
    }
    if(2==inputRegisterEntries){
      Serial.print("extractAirTemp: ");
      Serial.print(inputRegsBuffer[inputRegisterEntries]);
      Serial.println("°C");
    }
    
    
  }

  for(int holdingRegisterEntries = 0; holdingRegisterEntries < sizeOfHoldingRegisterBuffer; holdingRegisterEntries++){
    Serial.println(holdingRegsBuffer[holdingRegisterEntries]);
  }
  Serial.println("------------");

  // Delay between communication cycles to prevent overwhelming the bus
  delay(2000);
  modbus.clearResponseBuffer();
}
