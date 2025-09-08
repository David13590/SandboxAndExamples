#include <Arduino.h>

//Warning LED pins 
#define sensor1_green 4
#define sensor1_yellow 2
#define sensor1_red 15

#define sensor2_green 19
#define sensor2_yellow 18
#define sensor2_red 5

#define sensor3_green 32
#define sensor3_yellow 33
#define sensor3_red 25

void setup(){
    pinMode(sensor1_green, OUTPUT);
    pinMode(sensor1_yellow, OUTPUT);
    pinMode(sensor1_red, OUTPUT);

    pinMode(sensor2_green, OUTPUT);
    pinMode(sensor2_yellow, OUTPUT);
    pinMode(sensor2_red, OUTPUT);
    
    pinMode(sensor3_green, OUTPUT); 
    pinMode(sensor3_yellow, OUTPUT);
    pinMode(sensor3_red, OUTPUT);
}
void loop(){
    //Sensor1    
    digitalWrite(sensor1_green, HIGH);
    delay(1000);
    digitalWrite(sensor1_green, LOW);
    
    digitalWrite(sensor1_yellow, HIGH);
    delay(1000);
    digitalWrite(sensor1_yellow, LOW);
    
    digitalWrite(sensor1_red, HIGH);
    delay(1000);
    digitalWrite(sensor1_red, LOW);

    //Sensor2
    digitalWrite(sensor2_green, HIGH);
    delay(1000);
    digitalWrite(sensor2_green, LOW);
    
    digitalWrite(sensor2_yellow, HIGH);
    delay(1000);
    digitalWrite(sensor2_yellow, LOW);
    
    digitalWrite(sensor2_red, HIGH);
    delay(1000);
    digitalWrite(sensor2_red, LOW);

    //Sensor3
    digitalWrite(sensor3_green, HIGH);
    delay(1000);
    digitalWrite(sensor3_green, LOW);
    
    digitalWrite(sensor3_yellow, HIGH);
    delay(1000);
    digitalWrite(sensor3_yellow, LOW);
    
    digitalWrite(sensor3_red, HIGH);
    delay(1000);
    digitalWrite(sensor3_red, LOW);
}
