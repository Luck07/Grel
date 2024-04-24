#include "./mpu.h"

void setup() {
  Serial.begin(9600);
  MPU::begin();

<<<<<<< HEAD
  //MPU::mpu.calcOffsets(true, true);
  MPU::calibrar_offsets();
  Serial.print(" ");
  delay(2000);
=======
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
>>>>>>> 359d578103cd4b2a6e82005846e687937156712c
}

void loop() {
  MPU::update();

<<<<<<< HEAD
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
=======
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
>>>>>>> 359d578103cd4b2a6e82005846e687937156712c
