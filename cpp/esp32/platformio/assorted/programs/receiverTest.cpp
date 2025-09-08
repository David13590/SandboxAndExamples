#include <esp_now.h>
#include <WiFi.h>
#include <wire.h>
//#include "receiver.hpp"

///////////////////////////////////
//______________HPP______________//
///////////////////////////////////
typedef struct channel_data{
    int channel1;
    int channel2;
    bool channel3;
    int channel4;
    int channel5;
    bool channel6;
    bool channel7;
    bool channel8;
} channel_data;

typedef struct saved_channel_data{
    int JoyLeftX;
    int JoyLeftY;
    bool JoyLeftButton;
    int JoyRightX;
    int JoyRightY;
    bool JoyRightButton;
    bool pcbLeftButton;
    bool pcbRightButton;
} saved_channel_data;

void receiver_setup();
void receiverTest();
saved_channel_data& get_saved_channel_data();


// Create structs to save data
channel_data channelValue;
saved_channel_data saved_data;

///////////////////////////////////
//______________HPP______________//
///////////////////////////////////


// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&channelValue, incomingData, sizeof(channelValue));

  saved_data.JoyLeftX = channelValue.channel1;
  saved_data.JoyLeftY = channelValue.channel2;
  saved_data.JoyLeftButton = channelValue.channel3;
  saved_data.JoyRightX = channelValue.channel4;
  saved_data.JoyRightY = channelValue.channel5;
  saved_data.JoyRightButton = channelValue.channel6;
  saved_data.pcbLeftButton = channelValue.channel7;
  saved_data.pcbRightButton = channelValue.channel8;
}

saved_channel_data& get_saved_channel_data(){
  return saved_data;
}

void setup() {
  Serial.begin(115200);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}

int deadZoneMin = 400;
int deadZoneMax = 500;
void loop(){
  Serial.print(" joy1x: ");
  Serial.print(channelValue.channel1);
  Serial.print(" joy1y: ");
  Serial.print(channelValue.channel2);
  Serial.print(" knap1: ");
  Serial.print(channelValue.channel3);
  Serial.print("\t joy2x: ");
  Serial.print(channelValue.channel4);
  Serial.print(" joy2y: ");
  Serial.print(channelValue.channel5);
  Serial.print(" knap2: ");
  Serial.print(channelValue.channel6);
  Serial.print(" pcbButtonLeft: ");
  Serial.print(channelValue.channel7);
  Serial.print(" pcbButtonRight: ");
  Serial.println(channelValue.channel8);

  if(saved_data.JoyLeftX > deadZoneMin && saved_data.JoyLeftX < deadZoneMax){
    Serial.print("Idle");
  }
  if(saved_data.JoyLeftX < deadZoneMin){
    Serial.print("Backward");
  }
  if(saved_data.JoyLeftX > deadZoneMax){
    Serial.print("Forward");
  }
}
