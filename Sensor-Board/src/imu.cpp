#include "imu.h"

//Included Libraries
#include <Arduino.h>
#include <Wire.h>

//IMU Libraries
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

//IMU Pins
const uint8_t imu_scl = 35;
const uint8_t imu_sda = 34;
const uint8_t imu_int = 27;

Adafruit_MPU6050 mpu;

void imu_setup(){
    Wire.begin(imu_sda, imu_scl);
}

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
