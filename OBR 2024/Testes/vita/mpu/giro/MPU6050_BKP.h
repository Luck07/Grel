#ifndef _MPU6050_BKP_H
#define _MPU6050_BKP_H

#include "Arduino.h"
#include "Wire.h"

/**FILTRO PASSA BAIXA  (0x1a)
 *  CFG BandWith AccDelay GyroDelay
 * 0x00   260 Hz   0.0 ms   0.98 ms
 * 0x01   184 Hz   2.0 ms    1.9 ms
 * 0x02    94 Hz   3.0 ms    2.8 ms
 * 0x03    44 Hz   4.9 ms    4.8 ms
 * 0x04    21 Hz   8.5 ms    8.3 ms
 * 0x05    10 Hz  13.8 ms   13.4 ms
 * 0x06     5 Hz  19.8 ms   18.6 ms 
*/

/**GYRO RANGE (0x1b)
 *   FS_SEL FullScaleRange LSB_sensitivity 
 * 0  (0x0)   +-  250 dg/s    131 LSB/dg/s
 * 1  (0x8)   +-  500 dg/s   65.5 LSB/dg/s
 * 2 (0x10)   +- 1000 dg/s   32.8 LSB/dg/s
 * 3 (0x18)   +- 2000 dg/s   16.4 LSB/dg/s
*/

/**ACCL RANGE (0x1c)
 *  AFS_SEL FullScaleRange LSB_sensitivity
 * 0  (0x0)        +-  2 g     16384 LSB/g
 * 1  (0x8)        +-  4 g      8192 LSB/g
 * 2 (0x10)        +-  8 g      4096 LSB/g
 * 3 (0x18)        +- 16 g      2048 LSB/g
*/
    
#define MPU6050_ADDR            0x68 // i2c address
#define MPU6050_SMPRT_DIV_REG   0x19 // Sample Rate Divider
#define MPU6050_PWR_MGM_1_REG   0x6b // Power Management 1
#define MPU6050_CONFIG_REG      0X1a // Configuration
#define MPU6050_GYRO_CONFIG_REG 0X1b // Gyroscope Configuration
#define MPU6050_ACCL_CONFIG_REG 0X1c // Accelerometer Configuration
#define MPU6050_ACCL_OUT_REG    0X3b // Accelerometer Measurements (3b-40)
#define MPU6050_TEMP_OUT_REG    0x41 // Temperature Measurement    (41-42)
#define MPU6050_GYRO_OUT_REG    0X43 // Gyroscope Measurements     (43-48)

#define MPU6050_CONFIG_260_Hz 0x00
#define MPU6050_CONFIG_184_Hz 0x01
#define MPU6050_CONFIG_94_Hz  0x02
#define MPU6050_CONFIG_44_Hz  0x03
#define MPU6050_CONFIG_21_Hz  0x04
#define MPU6050_CONFIG_10_Hz  0x05
#define MPU6050_CONFIG_5_Hz   0x06

#define MPU6050_GYRO_250_DGpS  0x0
#define MPU6050_GYRO_500_DGpS  0x8
#define MPU6050_GYRO_1000_DGpS 0x10
#define MPU6050_GYRO_2000_DGpS 0x18

#define MPU6050_ACCL_2_G  0x0
#define MPU6050_ACCL_4_G  0x8
#define MPU6050_ACCL_8_G  0x10
#define MPU6050_ACCL_16_G 0x18

class MPU6050 {
public:
    MPU6050(TwoWire& w);
    byte begin(int gyro_config=MPU6050_GYRO_500_DGpS, int accl_config=MPU6050_ACCL_2_G);
    byte set_gyro_config(int config);
    byte set_accl_config(int config);

    void update();

    void calibrar_offsets(int total=500, bool print=false, bool gyro=true, bool accl=true);
    void set_gyro_offsets(float x, float y, float z);
    void set_accl_offsets(float x, float y, float z);

    float get_gyro_Xoffset() { return _gyro_Xoffset; }
    float get_gyro_Yoffset() { return _gyro_Yoffset; }
    float get_gyro_Zoffset() { return _gyro_Zoffset; }
    float get_accl_Xoffset() { return _accl_Xoffset; }
    float get_accl_Yoffset() { return _accl_Yoffset; }
    float get_accl_Zoffset() { return _accl_Zoffset; }

    float gyroX() { return _gyroX; }
    float gyroY() { return _gyroY; }
    float gyroZ() { return _gyroZ; }
    float acclX() { return _acclX; }
    float acclY() { return _acclY; }
    float acclZ() { return _acclZ; }

    float accl_angleX() { return _accl_angleX; }
    float accl_angleY() { return _accl_angleY; }

    // float yaw()   { return _angleZ; }
    // float pitch() { return _angleY; }
    // float roll()  { return _angleX; }

    // roll e pitch trocados por caudsa da posicao do mpu
    //float yaw()   { return  _angleZ; }
    //float pitch() { return -_angleX; }
    //float roll()  { return  _angleY; }
    //void reset_yaw()   { _angleZ = 0; }
    //void reset_pitch() { _angleX = 0; }
    //void reset_roll()  { _angleY = 0; }

    float yaw()   { return  _angleX; }
    float pitch() { return -_angleZ; }
    float roll()  { return  _angleY; }
    void reset_yaw()   { _angleX = 0; }
    void reset_pitch() { _angleZ = 0; }
    void reset_roll()  { _angleY = 0; }

    float temp() { return _temp; }
private:
    TwoWire* wire;
    float _lsb_to_DGpS, _lsb_to_g;
    float _gyro_Xoffset, _gyro_Yoffset, _gyro_Zoffset;
    float _accl_Xoffset, _accl_Yoffset, _accl_Zoffset;
    float _gyroX, _gyroY, _gyroZ;
    float _acclX, _acclY, _acclZ;
    float _temp;
    float _accl_angleX, _accl_angleY;
    float _angleX, _angleY, _angleZ;
    unsigned long _yaw_int_interval;

    byte write_data(byte reg, byte data);
    byte read_data(byte reg);
    void fetch_raw();
};

#endif