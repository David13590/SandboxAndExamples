#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

#define VRX_PIN  34 // ESP32 pin GPIO39 (ADC3) connected to VRX pin
#define VRY_PIN  35 // ESP32 pin GPIO36 (ADC0) connected to VRY pin
#define SW_PIN   32 // ESP32 pin GPIO17 connected to SW  pin

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xd0, 0xef, 0x76, 0xef, 0xea, 0xe0};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// OnDataSent is a CB call back function called when data has been sent.
// ESP_NOW_SEND_SUCCESS at a low-level checks with the receiver that data was received
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.print(status == ESP_NOW_SEND_SUCCESS ? " Delivery Success" : " Delivery Fail");
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.print(" Error initializing ESP-NOW");
    return;
  }

  // Once ESP-NOW is successfully Init, register the function OnDataSent
  // as a CB Call Back function with ESP to get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Assemble communication information about a network peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  // Add peer to the ESP peer list. It is not checked if the peer is present.
  if (esp_now_add_peer(&peerInfo) != ESP_OK){ 
    Serial.print(" Failed to add peer");
    return;
  }
}

void loop() {
  // Set values to send
  //strcpy(myData.a, "HEllo WORLD");
  myData.b = analogRead(VRX_PIN);
  myData.c = analogRead(VRY_PIN);
  myData.d = analogRead(SW_PIN);

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.print(" Sent with success");
  }
  else {
    Serial.print(" Error sending the data");
  }
  delay(200);
}