#include "./mpu.h"

void setup() {
  Serial.begin(9600);
  MPU::begin();

  //MPU::mpu.calcOffsets(true, true);
  MPU::calibrar_offsets();
  Serial.print(" ");
  delay(2000);
}

void loop() {
  MPU::update();

  // Serial.print("gyro xyz ");
  // Serial.print(MPU::gyroX()); Serial.print("\t");
  // Serial.print(MPU::gyroY()); Serial.print("\t");
  // Serial.println(MPU::gyroZ());

  // Serial.print("acc xyz ");
  // Serial.print(MPU::accX()); Serial.print("\t");
  // Serial.print(MPU::accY()); Serial.print("\t");
  // Serial.println(MPU::accZ());

  Serial.print("roll(x):");
  Serial.print(MPU::roll());
  Serial.print(",");
  Serial.print("pitch(y):");
  Serial.print(MPU::pitch());
  Serial.print(",");
  Serial.print("yaw(z):");
  Serial.println(MPU::yaw());

  delay(10);
}