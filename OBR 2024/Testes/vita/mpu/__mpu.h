/* The register map is provided at
 * https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
 *
 * Mapping of the different gyro and accelero configurations:
 *
 * GYRO_CONFIG_[0,1,2,3] range = +- [250, 500,1000,2000] deg/s
 *                       sensi =    [131,65.5,32.8,16.4] bit/(deg/s)
 *
 * ACC_CONFIG_[0,1,2,3] range = +- [    2,   4,   8,  16] times the gravity (9.81 m/s^2)
 *                      sensi =    [16384,8192,4096,2048] bit/gravity
*/

#define byte char

#ifndef _MPU_H
#define _MPU_H

#include "Arduino.h"
#include "Wire.h"

#define MPU6050_ADDR                  0x68
#define MPU6050_SMPLRT_DIV_REGISTER   0x19
#define MPU6050_CONFIG_REGISTER       0x1a
#define MPU6050_GYRO_CONFIG_REGISTER  0x1b
#define MPU6050_ACC_CONFIG_REGISTER   0x1c
#define MPU6050_PWR_MGMT_1_REGISTER   0x6b
#define MPU6050_GYRO_OUT_REGISTER     0x43
#define MPU6050_ACC_OUT_REGISTER      0x3B

#define RAD_2_DEG             57.29578 // [deg/rad]
#define CALIB_OFFSET_NB_MES   500
#define TEMP_LSB_2_DEGREE     340.0    // [bit/celsius]
#define TEMP_LSB_OFFSET       12412.0

#define DEFAULT_GYRO_COEFF    0.98

#define GYRO_RANGE_250_DGpS  0
#define GYRO_RANGE_500_DGpS  1
#define GYRO_RANGE_1000_DGpS 2
#define GYRO_RANGE_2000_DGpS 3
#define ACC_RANGE_2_G  0
#define ACC_RANGE_4_G  1
#define ACC_RANGE_8_G  2
#define ACC_RANGE_16_G 3

namespace MPU {

  // private methods
  namespace {
    float gyro_lsb_to_dgs;
    float acc_lsb_to_g;

    byte write_data(byte reg, byte data) {
      Wire.beginTransmission(MPU6050_ADDR);
      Wire.write(reg);
      Wire.write(data);
      byte status = Wire.endTransmission();
      return status;
    }

    byte read_data(byte reg) {
      Wire.beginTransmission(MPU6050_ADDR);
      Wire.write(reg);
      Wire.endTransmission(true);
      Wire.requestFrom(MPU6050_ADDR, (uint8_t) 1);
      byte data = Wire.read();
      return data;
    }
  }

  byte begin(int gyro_range=1, int acc_range=0) {
    
  }

  byte set_gyro_range(int range_num) {
    byte status;
		/*   FS_SEL FullScaleRange LSB_sensitivity
		 * 0  (0x0)   +-  250 dg/s    131 LSB/dg/s
		 * 1  (0x8)   +-  500 dg/s   65.5 LSB/dg/s
		 * 2 (0x10)   +- 1000 dg/s   32.8 LSB/dg/s
		 * 3 (0x18)   +- 2000 dg/s   16.4 LSB/dg/s
		*/
    switch(range_num) {
      case GYRO_RANGE_250_DGpS:
        gyro_lsb_to_dgs = 131.0;
        status = write_data(MPU6050_GYRO_CONFIG_REGISTER, 0x00);
        break;
      case GYRO_RANGE_500_DGpS:
        gyro_lsb_to_dgs = 65.5;
        status = write_data(MPU6050_GYRO_CONFIG_REGISTER, 0x08);
        break;
      case GYRO_RANGE_1000_DGpS:
        gyro_lsb_to_dgs = 32.8;
        status = write_data(MPU6050_GYRO_CONFIG_REGISTER, 0x10);
        break;
      case GYRO_RANGE_2000_DGpS:
        gyro_lsb_to_dgs = 16.4;
        status = write_data(MPU6050_GYRO_CONFIG_REGISTER, 0x18);
        break;
      default:
        status = 1;
        break;
    }
    return status;
  }

  byte set_acc_config(int range_num) {
    byte status;
    /*  AFS_SEL FullScaleRange LSB_sensitivity
		 * 0  (0x0)         +-  2g     16384 LSB/g
		 * 1  (0x8)         +-  4g      8192 LSB/g
		 * 2 (0x10)         +-  8g      4096 LSB/g x
		 * 3 (0x18)         +- 16g      2048 LSB/g
		*/
    switch(range_num) {
      case ACC_RANGE_2_G:
        acc_lsb_to_g = 16384.0;
        status = write_data(MPU6050_ACC_CONFIG_REGISTER, 0x00);
        break;
      case ACC_RANGE_4_G:
        acc_lsb_to_g = 8192.0;
        status = write_data(MPU6050_ACC_CONFIG_REGISTER, 0x08);
        break;
      case ACC_RANGE_8_G:
        acc_lsb_to_g = 4096.0;
        status = write_data(MPU6050_ACC_CONFIG_REGISTER, 0x10);
        break;
      case ACC_RANGE_16_G:
        acc_lsb_to_g = 2048.0;
        status = write_data(MPU6050_ACC_CONFIG_REGISTER, 0x18);
        break;
        
    }
    return status;
  }

  
}

class MPU6050{
  public:
    // INIT and BASIC FUNCTIONS
	MPU6050(TwoWire &w);
    byte begin(int gyro_config_num=1, int acc_config_num=0);
	
	byte writeData(byte reg, byte data);
    byte readData(byte reg);
	
	void calcOffsets(bool is_calc_gyro=true, bool is_calc_acc=true);
	void calcGyroOffsets(){ calcOffsets(true,false); }; // retro-compatibility with v1.0.0
	void calcAccOffsets(){ calcOffsets(false,true); }; // retro-compatibility with v1.0.0
	
	void setAddress(uint8_t addr){ address = addr; };
	uint8_t getAddress(){ return address; };
	
	// MPU CONFIG SETTER
	byte setGyroConfig(int config_num);
	byte setAccConfig(int config_num);
	
    void setGyroOffsets(float x, float y, float z);
	void setAccOffsets(float x, float y, float z);
	
	void setFilterGyroCoef(float gyro_coeff);
	void setFilterAccCoef(float acc_coeff);

	// MPU CONFIG GETTER
	float getGyroXoffset(){ return gyroXoffset; };
    float getGyroYoffset(){ return gyroYoffset; };
    float getGyroZoffset(){ return gyroZoffset; };
	
	float getAccXoffset(){ return accXoffset; };
	float getAccYoffset(){ return accYoffset; };
	float getAccZoffset(){ return accZoffset; };
	
	float getFilterGyroCoef(){ return filterGyroCoef; };
	float getFilterAccCoef(){ return 1.0-filterGyroCoef; };
	
	// DATA GETTER
    float getTemp(){ return temp; };

    float getAccX(){ return accX; };
    float getAccY(){ return accY; };
    float getAccZ(){ return accZ; };

    float getGyroX(){ return gyroX; };
    float getGyroY(){ return gyroY; };
    float getGyroZ(){ return gyroZ; };
	
	float getAccAngleX(){ return angleAccX; };
    float getAccAngleY(){ return angleAccY; };

    float getAngleX(){ return angleX; };
    float getAngleY(){ return angleY; };
    float getAngleZ(){ return angleZ; };

	// INLOOP UPDATE
	void fetchData(); // user should better call 'update' that includes 'fetchData'
    void update();
	
	// UPSIDE DOWN MOUNTING
	bool upsideDownMounting = false;


  private:
    TwoWire *wire;
	uint8_t address = MPU6050_ADDR; // 0x68 or 0x69
	// float gyro_lsb_to_degsec, acc_lsb_to_g;
  //   float gyroXoffset, gyroYoffset, gyroZoffset;
	// float accXoffset, accYoffset, accZoffset;
  //   float temp, accX, accY, accZ, gyroX, gyroY, gyroZ;
  //   float angleAccX, angleAccY;
  //   float angleX, angleY, angleZ;
  //   long preInterval;
  //   float filterGyroCoef; // complementary filter coefficient to balance gyro vs accelero data to get angle
};

#endif

