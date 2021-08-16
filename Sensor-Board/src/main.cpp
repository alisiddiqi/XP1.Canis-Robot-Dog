/*
THINGS TO DO
Add the debug stuff:
  #define DEBUG

  #ifdef DEBUG
    Code things
  #endif

Add bitmask to mux array

Remove un-needed delays

Move all declarations to a separate header file

Move IMU and Ultrasonic code to another file to keep stuff clean
 and import them in, ei, IMU.c

IMU and Ultra code need to return data in a structure,
 not just print stuff

State why magic numbers exist

Account of integer division
 - https://www.informit.com/articles/article.aspx?p=2062174&seqNum=4#:~:text=Integer%20division%20yields%20an%20integer,used%20only%20with%20integer%20operands.

Add comments to void begin function

Sahil's UART comment:
So there's a bit of a difference to put, by opening the 
 serial object here with TX3 RX3 you're sending these 
 signals out over your RS485 bus instead of to the computer 
 now (i.e. you can no longer view the output of your print statements).
I am not sure if this was your intention given that you have characters inside here
I would look into the use of multiple UART peripherals
*/

//Headers
#include "ultrasonic.h"
#include "imu.h"

//Included Libraries
#include <Arduino.h>
#include <Wire.h>

#define DEBUG

//Communication Pins
const uint8_t RX3 = 12;
const uint8_t TX3 = 13;
const uint8_t re_enb = 42;
const uint8_t de_enb = 38;

//Indicator Pins
const uint8_t offboard_led = 39;
const uint8_t onboard_led = 41;
const uint8_t buzzer = 40;

//Changing I2C pins: https://randomnerdtutorials.com/esp32-i2c-communication-arduino-ide/#3

void setup(){

  //Setups
  imu_setup();
  ultrasonic_setup();

  //Communcation Pin Setups
  pinMode(re_enb, OUTPUT);
  pinMode(de_enb, OUTPUT);

  digitalWrite(re_enb, LOW);
  digitalWrite(de_enb, LOW);

  //Indicator Pin Setups
  pinMode(offboard_led, OUTPUT); 
  pinMode(onboard_led, OUTPUT); 
  pinMode(buzzer, OUTPUT); 

  digitalWrite(offboard_led, LOW);
  digitalWrite(onboard_led, LOW);
  digitalWrite(buzzer, LOW);

  //Communication
  Serial.begin(115200,SERIAL_8N1,TX3,RX3);
}

void loop(){
  imu_results();
  ultrasonic_results();

  #ifdef DEBUG
    delay(2000);
  #endif
  
}

#ifndef DEBUG
  void begin(unsigned long baud, uint32_t config=SERIAL_8N1, int8_t rxPin=-1, int8_t txPin=-1, bool invert=false, unsigned long timeout_ms = 20000UL);
#endif