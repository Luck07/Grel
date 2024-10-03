#ifndef _MPU_H
#define _MPU_H

#include <Arduino.h>
#include "Wire.h"
#include <MPU6050_light.h>

#define GYRO_RANGE_250_DGpS  0
#define GYRO_RANGE_500_DGpS  1
#define GYRO_RANGE_1000_DGpS 2
#define GYRO_RANGE_2000_DGpS 3
#define ACC_RANGE_2_G  0
#define ACC_RANGE_4_G  1
#define ACC_RANGE_8_G  2
#define ACC_RANGE_16_G 3

#include "Wire.h"
#include <MPU6050_light.h>

namespace MPU {

  namespace {
    float gyro_offset[] = {0.0, 0.0, 0.0}; // x y z
    float acc_offset[]  = {0.0, 0.0, 0.0}; // x y z
  }

  MPU6050 mpu(Wire);

  /*
  void calibrar_offsets(bool print=true, int t=2000) {

    for(int i=0; i<t; i++) {
      gyro_offset[0] += mpu.getGyroX();
      gyro_offset[1] += mpu.getGyroY();
      gyro_offset[2] += mpu.getGyroZ();
      acc_offset[0] += mpu.getAccX();
      acc_offset[1] += mpu.getAccY();
      acc_offset[2] += mpu.getAccZ() -1.0;

      if(print) {
        Serial.print(i); Serial.print("\t");
        Serial.print(gyro_offset[0]); Serial.print("/");
        Serial.print(gyro_offset[1]); Serial.print("/");
        Serial.print(gyro_offset[2]); Serial.print("\t");
        Serial.print(acc_offset[0]); Serial.print("/");
        Serial.print(acc_offset[1]); Serial.print("/");
        Serial.println(acc_offset[2]);
      //acc_offset[2] += mpu.getAccZ();

      delay(1);
    }
    gyro_offset[0] /= t;
    gyro_offset[1] /= t;
    gyro_offset[2] /= t;
    acc_offset[0] /= t;
    acc_offset[1] /= t;
    acc_offset[2] *= cos(10 * M_PI/180)/t;

    Serial.print("gyro offsets [x, y, z]: ");
    Serial.print(gyro_offset[0]); Serial.print(", ");
    Serial.print(gyro_offset[1]); Serial.print(", ");
    Serial.println(gyro_offset[2]);

    Serial.print("acc offsets  [x, y, z]: ");
    Serial.print(acc_offset[0]); Serial.print(", ");
    Serial.print(acc_offset[1]); Serial.print(", ");
    Serial.println(acc_offset[2]);

    mpu.setGyroOffsets(gyro_offset[0], gyro_offset[1], gyro_offset[2]);
    mpu.setAccOffsets(acc_offset[0], acc_offset[1], acc_offset[2]);
  }
  */

  
  void calibrar_offsets() {
    mpu.calcOffsets(true, true);
    //mpu.setAccOffsets(mpu.getAccXoffset(), mpu.getAccYoffset(), mpu.getAccZoffset()*cos(10 * M_PI/180));

    Serial.println(" ");
    Serial.print("gyro offsets [x, y, z]: ");
    Serial.print(mpu.getGyroXoffset()); Serial.print(", ");
    Serial.print(mpu.getGyroYoffset()); Serial.print(", ");
    Serial.println(mpu.getGyroZoffset());

    Serial.print("acc offsets  [x, y, z]: ");
    Serial.print(mpu.getAccXoffset()); Serial.print(", ");
    Serial.print(mpu.getAccYoffset()); Serial.print(", ");
    Serial.println(mpu.getAccZoffset());
  }

  void gyro_offsets(float x, float y, float z) { mpu.setGyroOffsets(x, y, z); };
  void acc_offsets(float x, float y, float z)  { mpu.setAccOffsets(x, y, z); };

  byte begin(int gyro_range=1, int acc_range=0) { 
    Wire.begin();
    return mpu.begin(gyro_range, acc_range);
  };

  void update() { mpu.update(); };

  float gyroX() { return mpu.getGyroX(); };
  float gyroY() { return mpu.getGyroY(); };
  float gyroZ() { return mpu.getGyroZ(); };

  float accX() { return mpu.getAccX(); };
  float accY() { return mpu.getAccY(); };
  float accZ() { return mpu.getAccZ(); };


  // roll e pitch trocados por caudsa da posicao do mpu
  float roll()  { return  mpu.getAngleY(); }; 
  float pitch() { return -mpu.getAngleX(); };
  float yaw()   { return  mpu.getAngleZ(); };

}

#endif