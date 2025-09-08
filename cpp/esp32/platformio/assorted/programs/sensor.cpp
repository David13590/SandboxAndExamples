#include <Wire.h>
#include <VL53L0X.h>

#define xshut1 15
#define xshut2 33

VL53L0X sensor1;
VL53L0X sensor2;

void setup(){

  
  pinMode(xshut1, OUTPUT);
  pinMode(xshut2, OUTPUT);

  //Turn off sensors
  digitalWrite(xshut1, LOW); //xshut is actvie low
  digitalWrite(xshut2, LOW);


  Wire.begin(); // Start wire
  Serial.begin(115200);

  //Sensor1 setup
  digitalWrite(xshut1, HIGH); //Turn on sensor1
  delay(150);
  sensor1.init(true);
  sensor1.setAddress((uint8_t)01); //New address

  //Sensor2 setup
  digitalWrite(xshut2, HIGH);
  delay(150);
  sensor2.init(true);
  sensor2.setAddress((uint8_t)02);

  //Start measuring
  sensor1.startContinuous();
  sensor2.startContinuous();

}

void loop()
{
  Serial.print("Sensor1 ");
  int sensorPrint1 = sensor1.readRangeContinuousMillimeters();
  Serial.print(sensorPrint1);

  Serial.print(" Sensor2 ");
  int sensorPrint2 = sensor2.readRangeContinuousMillimeters();
  Serial.print(sensorPrint2);

  Serial.println();
}
