#include "./mpu.h"

void setup() {
  Serial.begin(9600);
  MPU::begin();

  //MPU::calibrar_offsets(true);
  MPU::gyro_offsets(0.46, -0.76, 0.76);
  MPU::acc_offsets(0.01, -0.13, cos(10 * M_PI/180));

  Serial.print(MPU::mpu.getGyroXoffset()); Serial.print(", ");
  Serial.print(MPU::mpu.getGyroYoffset()); Serial.print(", ");
  Serial.println(MPU::mpu.getGyroZoffset());
  Serial.print(MPU::mpu.getAccXoffset()); Serial.print(", ");
  Serial.print(MPU::mpu.getAccYoffset()); Serial.print(", ");
  Serial.println(MPU::mpu.getAccZoffset());

  delay(1000);
}

void loop() {
  MPU::update();

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
