//#include "./mpu.h"
#include <Wire.h>
#include "MPU6050_BKP.h"
MPU6050 mpu(Wire);


void setup() {
  Serial.begin(9600);
  mpu.begin();
  // MPU::begin();

  // //MPU::mpu.calcOffsets(true, true);
  mpu.calibrar_offsets();
  delay(1000);

  // MPU::calibrar_offsets();
  // Serial.print(" ");
  // delay(2000);
}

void loop() {
  mpu.update();

  float yaw = mpu.yaw();
  float pit = mpu.pitch();
  float rol = mpu.roll();
  //if(yaw >= (90.0 - (90.0*5.0/100.0)) || yaw <= -90.0 + (90.0*5.0/100.0)) mpu.reset_yaw();

  // Serial.print("gyro xyz ");
  // Serial.print(MPU::gyroX()); Serial.print("\t");
  // Serial.print(MPU::gyroY()); Serial.print("\t");
  // Serial.println(MPU::gyroZ());

  // Serial.print("acc xyz ");
  // Serial.print(MPU::accX()); Serial.print("\t");
  // Serial.print(MPU::accY()); Serial.print("\t");
  // Serial.println(MPU::accZ());

  Serial.print("roll(x):");
  Serial.print(rol);
  Serial.print(",");
  Serial.print("pitch(y):");
  Serial.print(pit);
  Serial.print(",");
  Serial.print("yaw(z):");
  Serial.println(yaw);

  delay(10);
}