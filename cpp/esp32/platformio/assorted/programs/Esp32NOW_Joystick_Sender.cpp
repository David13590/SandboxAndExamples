#include <esp_now.h>
#include <WiFi.h>
#include <Arduino.h>
#include <Wire.h>
#include <ezButton.h>

#define VRX_PIN  34
#define VRY_PIN  35
#define SW_PIN   32

//Receiver Mads: 0xd0, 0xef, 0x76, 0xf0, 0x11, 0xd8
uint8_t broadcastAddress[] = {0xd0, 0xef, 0x76, 0xf0, 0x11, 0xd8};
ezButton button(SW_PIN);
const float pinOutputVolt = 3.3; 
const int joystickMaxRead = 4095;

typedef struct struct_message {
  int x;
  int y;
  float xVolt;
  float yVolt;
  bool button;
  
} struct_message;

// Create a struct_message called myData
struct_message myJoystickValues;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status: ");
  Serial.print(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  analogSetAttenuation(ADC_11db);
  button.setDebounceTime(100);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.print("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.print(" Failed to add peer");
    return;
  }
}
 
void loop() {
  button.loop(); // Set values to send
  myJoystickValues.x = analogRead(VRX_PIN);
  myJoystickValues.y = analogRead(VRY_PIN);
  myJoystickValues.xVolt = myJoystickValues.x*(pinOutputVolt/joystickMaxRead); 
  myJoystickValues.yVolt = myJoystickValues.y*(pinOutputVolt/joystickMaxRead);
  myJoystickValues.button = digitalRead(SW_PIN);
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myJoystickValues, sizeof(myJoystickValues));
   
  if (result != ESP_OK) {
    Serial.print(", Error sending the data");
  }
  
  Serial.print("\t joy1x: ");
  Serial.print(myJoystickValues.x);
  Serial.print(" voltX: ");
  Serial.print(myJoystickValues.xVolt);

  Serial.print(" joy1y: ");
  Serial.print(myJoystickValues.y);
  Serial.print(" voltY: ");
  Serial.print(myJoystickValues.yVolt);

  Serial.print(" knap: ");
  Serial.print(myJoystickValues.button);

  delay(100);
}