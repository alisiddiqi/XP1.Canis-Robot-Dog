//Included Libraries
#include <Arduino.h>
#include <Wire.h>

//IMU Libraries
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

//Ultrasonic Pins
const int ultrasonic_echo = 5;
const int mux_trig = 14;
const int mux_0 = 15;
const int mux_1 = 16;
const int mux_2 = 25;
const int mux_3 = 24;

//IMU Pins
const int imu_scl = 35;
const int imu_sda = 34;
const int imu_int = 27;

//Communication Pins
const int RX3 = 12;
const int TX3 = 13;
const int re_enb = 42;
const int de_enb = 38;

//Indicator Pins
const int offboard_led = 39;
const int onboard_led = 41;
const int buzzer = 40;

//Changing I2C pins: https://randomnerdtutorials.com/esp32-i2c-communication-arduino-ide/#3

Adafruit_MPU6050 mpu;

void setup(){
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
  Wire.begin(imu_sda, imu_scl);
  Serial.begin(115200,SERIAL_8N1,TX3,RX3);
}

void loop(){
  imu_results();
  ultrasonic_results();
  delay(2000);
}

void begin(unsigned long baud, uint32_t config=SERIAL_8N1, int8_t rxPin=-1, int8_t txPin=-1, bool invert=false, unsigned long timeout_ms = 20000UL);

void imu_results(){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("Accelerometer ");
  Serial.print("X: ");
  Serial.print(a.acceleration.x, 1);
  Serial.print(" m/s^2, ");
  Serial.print("Y: ");
  Serial.print(a.acceleration.y, 1);
  Serial.print(" m/s^2, ");
  Serial.print("Z: ");
  Serial.print(a.acceleration.z, 1);
  Serial.println(" m/s^2");

  Serial.print("Gyroscope ");
  Serial.print("X: ");
  Serial.print(g.gyro.x, 1);
  Serial.print(" rps, ");
  Serial.print("Y: ");
  Serial.print(g.gyro.y, 1);
  Serial.print(" rps, ");
  Serial.print("Z: ");
  Serial.print(g.gyro.z, 1);
  Serial.println(" rps");
  delay(100);
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