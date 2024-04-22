#ifndef _MPU_H
#define _MPU_H

#include "Wire.h"
#include <MPU6050_light.h>

namespace MPU {

  namespace {
    float gyro_offset[] = {0.0, 0.0, 0.0}; // x y z
    float acc_offset[]  = {0.0, 0.0, cos(10 * M_PI/180)}; // x y z
  }

  MPU6050 mpu(Wire);

  void calibrar_offsets(bool print=true, int t=2000) {

    for(int i=0; i<t; i++) {
      gyro_offset[0] += mpu.getGyroX();
      gyro_offset[1] += mpu.getGyroY();
      gyro_offset[2] += mpu.getGyroZ();
      acc_offset[0] += mpu.getAccX();
      acc_offset[1] += mpu.getAccY();
      //acc_offset[2] += mpu.getAccZ();

      if(print) {
        Serial.print(i); Serial.print("\t");
        Serial.print(gyro_offset[0]); Serial.print("\t");
        Serial.print(gyro_offset[1]); Serial.print("\t");
        Serial.print(gyro_offset[2]); Serial.print("\t");
        Serial.print(acc_offset[0]); Serial.print("\t");
        Serial.print(acc_offset[1]); Serial.println("\t");
        //Serial.println(acc_offset[2]);
      }

      delay(1);
    }
  
  gyro_offset[0] /= t;
  gyro_offset[1] /= t;
  gyro_offset[2] /= t;
  acc_offset[0] /= t;
  acc_offset[1] /= t;
  //acc_offset[2] /= t;

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

  void gyro_offsets(float x, float y, float z) { mpu.setGyroOffsets(x, y, z); };
  void acc_offsets(float x, float y, float z) { mpu.setAccOffsets(x, y, z); };

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

  float roll()  { return -mpu.getAngleX(); };
  float pitch() { return mpu.getAngleY(); };
  float yaw()   { return mpu.getAngleZ(); };

}

#endif
