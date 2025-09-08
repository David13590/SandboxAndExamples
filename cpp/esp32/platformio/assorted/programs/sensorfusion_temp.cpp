#include <Arduino.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>


Adafruit_BMP280 bmp;
float pressure;   //To store the barometric pressure (Pa)
float temperature;  //To store the temperature (oC)
int altimeter;
#define BMPPIN 15
#define DHTTYPE DHT11

// --- DS18B20 setup ---
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature ds18b20(&oneWire);

void setup() {
  Serial.begin(115200);
  bmp.begin(0x76);
  ds18b20.begin();
  delay(1000);
}

void loop() {
  // Læs BMP
  pressure = bmp.readPressure();
  temperature = bmp.readTemperature();
  altimeter = bmp.readAltitude (1050.35);

  // Læs DS18B20
  ds18b20.requestTemperatures();
  float temp_ds18b20 = ds18b20.getTempCByIndex(0);  // første sensor på bus

  // Tjek fejl
  
    Serial.print("BMP: ");
    Serial.print(temperature);
    Serial.print(" °C | Tryk: ");
    Serial.print(pressure);
    Serial.print("  Højde: ");
    Serial.println(altimeter);

    Serial.print("DS18B20: ");
    Serial.print(temp_ds18b20);
    Serial.println(" °C");
  


  // Tag gennemsnit af de to temperaturer
  if (!isnan(temperature) && temp_ds18b20 != DEVICE_DISCONNECTED_C) {
    float fused_temp = (temperature + temp_ds18b20) / 2.0;

    Serial.print("Temperatur gennemsnit: ");
    Serial.print(fused_temp);
    Serial.println(" °C");
  }

  delay(1000);
}
