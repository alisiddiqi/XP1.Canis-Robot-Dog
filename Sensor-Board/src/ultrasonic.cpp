#include "ultrasonic.h"

//Included Libraries
#include <Arduino.h>

//Ultrasonic Pins
const uint8_t ultrasonic_echo = 5;
const uint8_t mux_trig = 14;
const uint8_t mux_0 = 15;
const uint8_t mux_1 = 16;
const uint8_t mux_2 = 25;
const uint8_t mux_3 = 24;

void ultrasonic_setup(){
//Ultrasonic Pin Setups
    pinMode(ultrasonic_echo, INPUT);
    pinMode(mux_trig, OUTPUT); 
    pinMode(mux_0, OUTPUT); 
    pinMode(mux_1, OUTPUT); 
    pinMode(mux_2, OUTPUT); 
    pinMode(mux_3, OUTPUT); 

    digitalWrite(ultrasonic_echo, LOW);
    digitalWrite(mux_0, LOW);
    digitalWrite(mux_1, LOW);
    digitalWrite(mux_2, LOW);
    digitalWrite(mux_3, LOW);
}

void ultrasonic_results(){
  //Loop through and read all 16 values
  for(int i = 11; i < 16; i ++){
    Serial.print("Value at channel ");
    Serial.print(i);
    Serial.print(" is: ");
    Serial.print(readMux(i));
    Serial.println(" cm");
  }
  delay(100);
}

float readMux(int channel){
  int controlPin[] = {mux_0, mux_1, mux_2, mux_3};

  int muxChannel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  //return the value
  long duration, inches, cm;
   pinMode(mux_trig, OUTPUT);
   digitalWrite(mux_trig, LOW);
   delayMicroseconds(2);
   digitalWrite(mux_trig, HIGH);
   delayMicroseconds(10);
   digitalWrite(mux_trig, LOW);
   pinMode(ultrasonic_echo, INPUT);
   duration = pulseIn(ultrasonic_echo, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   delay(100);
   return cm;
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}