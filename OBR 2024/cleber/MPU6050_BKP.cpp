#include "MPU6050_BKP.h"
#include "Arduino.h"

MPU6050::MPU6050(TwoWire& w) {
    wire = &w;
    set_gyro_offsets(0, 0, 0);
    set_accl_offsets(0, 0, 0);
}

byte MPU6050::write_data(byte reg, byte data) {
    wire->beginTransmission(MPU6050_ADDR);
    wire->write(reg);
    wire->write(data);
    byte st = wire->endTransmission();
    return st;
}

byte MPU6050::read_data(byte reg) {
    wire->beginTransmission(MPU6050_ADDR);
    wire->write(reg);
    wire->endTransmission(true);
    wire->requestFrom(MPU6050_ADDR, (uint8_t)1);
    byte data = wire->read();
    return data;
}

void MPU6050::fetch_raw() {
    wire->beginTransmission(MPU6050_ADDR);
    // accl: 0x3b-0x40 = 59-64,
    // temp: 0x41-0x42 = 65-66,
    // gyro: 0x43-0x48 = 67-72
    // total: 0x3b-0x48 = 59-72
    wire->write(MPU6050_ACCL_OUT_REG);
    wire->endTransmission(false);
    wire->requestFrom(MPU6050_ADDR, (uint8_t)14);

    int16_t raw_data[7]; // [ax,ay,az, temp, gx,gy,gz]

    for(int i=0; i<7; i++) {
        raw_data[i]  = wire->read() << 8;
        raw_data[i] |= wire->read();
    }

    _acclX = ((float)raw_data[0])/_lsb_to_g - _accl_Xoffset;
    _acclY = ((float)raw_data[1])/_lsb_to_g - _accl_Yoffset;
    _acclZ = ((float)raw_data[2])/_lsb_to_g - _accl_Zoffset;

    _temp = (raw_data[3] + 12412.0/*lsb_offset*/)/340.0/*lsb_to_deg*/;

    _gyroX = ((float)raw_data[4])/_lsb_to_DGpS - _gyro_Xoffset;
    _gyroY = ((float)raw_data[5])/_lsb_to_DGpS - _gyro_Yoffset;
    _gyroZ = ((float)raw_data[6])/_lsb_to_DGpS - _gyro_Zoffset;
    //if(_gyroZ>0 && _gyroZ< 0.4) _gyroZ = 0;
    //if(_gyroZ<0 && _gyroZ>-0.4) _gyroZ = 0;
}

static float wrap(float angle,float limit){
  while (angle >  limit) angle -= 2*limit;
  while (angle < -limit) angle += 2*limit;
  return angle;
}

void MPU6050::update() {
    this->fetch_raw();

    float sign_z = _acclZ<0 ? -1 : 1;
    _accl_angleX =  atan2(_acclY, sign_z*sqrt(_acclZ*_acclZ + _acclX*_acclX)) * (180.0/M_PI);
    _accl_angleY = -atan2(_acclX,        sqrt(_acclZ*_acclZ + _acclY*_acclY)) * (180.0/M_PI);

    unsigned long mil = millis();
    float dt = (mil - _yaw_int_interval) * 1e-3;
    _yaw_int_interval = mil;

    _angleX = wrap(0.98*(_accl_angleX + wrap(_angleX +        _gyroX*dt - _accl_angleX,180)) + 0.02*_accl_angleX,180);
    _angleY = wrap(0.98*(_accl_angleY + wrap(_angleY + sign_z*_gyroY*dt - _accl_angleY, 90)) + 0.02*_accl_angleY, 90);
    _angleZ += _gyroZ * dt; //  ∫ Gz(t) dt = Yaw(t) ~~ ∑ Gz(t-1)*dt
}

byte MPU6050::begin(int gyro_config, int accl_config) {
    byte st = write_data(MPU6050_PWR_MGM_1_REG, 0x01); //PLL with X axis gyro reference
    write_data(MPU6050_SMPRT_DIV_REG, 0x00); // SampleRate = GyroOutputRate/(1 + (SMPRT_DIV=0)) = GyroOutputRate
    write_data(MPU6050_CONFIG_REG, MPU6050_CONFIG_260_Hz);
    set_gyro_config(gyro_config);
    set_accl_config(accl_config);

    this->update();
    _angleX = this->accl_angleX();
    _angleY = this->accl_angleY();
    _yaw_int_interval = millis();
    return st;
}

byte MPU6050::set_gyro_config(int config) {
    byte st;
    switch(config) {
        case MPU6050_GYRO_250_DGpS:  _lsb_to_DGpS = 131.0; break;
        case MPU6050_GYRO_500_DGpS:  _lsb_to_DGpS =  65.5; break;
        case MPU6050_GYRO_1000_DGpS: _lsb_to_DGpS =  32.8; break;
        case MPU6050_GYRO_2000_DGpS: _lsb_to_DGpS =  16.4; break;
        default: st = 1; return st;
    }
    st = write_data(MPU6050_GYRO_CONFIG_REG, config);
    return st;
}

byte MPU6050::set_accl_config(int config) {
    byte st;
    switch(config) {
        case MPU6050_ACCL_2_G:  _lsb_to_g = 16384.0; break;
        case MPU6050_ACCL_4_G:  _lsb_to_g =  8192.0; break;
        case MPU6050_ACCL_8_G:  _lsb_to_g =  4096.0; break;
        case MPU6050_ACCL_16_G: _lsb_to_g =  2048.0; break;
        default: st = 1; return st;
    }
    st = write_data(MPU6050_ACCL_CONFIG_REG, config);
    return st;
}

void MPU6050::set_gyro_offsets(float x, float y, float z) {
    _gyro_Xoffset = x;
    _gyro_Yoffset = y;
    _gyro_Zoffset = z;
}

void MPU6050::set_accl_offsets(float x, float y, float z) {
    _accl_Xoffset = x;
    _accl_Yoffset = y;
    _accl_Zoffset = z;
}

void MPU6050::calibrar_offsets(int total, bool print, bool gyro, bool accl) {
    if(gyro) set_gyro_offsets(0, 0, 0);
    if(accl) set_accl_offsets(0, 0, 0);

    float sums[6] = {0,0,0 , 0,0,0};//3*accl, 3*gyro

    for(int i=0; i<total; i++) {
        this->fetch_raw();
        sums[0] += _acclX;
        sums[1] += _acclY;
        sums[2] += _acclZ - 1; //_acclZ - cos(10 * M_PI/180);
        sums[3] += _gyroX;
        sums[4] += _gyroY;
        sums[5] += _gyroZ;

        if(print) {
            Serial.print(i); Serial.print("\t");
            Serial.print(sums[3]); Serial.print(" / "); //gX
            Serial.print(sums[4]); Serial.print(" / "); //gY
            Serial.print(sums[5]); Serial.print("\t");  //gZ
            Serial.print(sums[0]); Serial.print(" / "); //aX
            Serial.print(sums[1]); Serial.print(" / "); //aY
            Serial.println(sums[2]);                    //aZ
        }
        delay(1);
    }

    if(accl) {
        _accl_Xoffset = sums[0]/total;
        _accl_Yoffset = sums[1]/total;
        _accl_Zoffset = sums[2]/total;
    }

    if(gyro) {
        _gyro_Xoffset = sums[3]/total;
        _gyro_Yoffset = sums[4]/total;
        _gyro_Zoffset = sums[5]/total;
    }

    Serial.print("gyro offsets [x, y, z]: ");
    Serial.print(_gyro_Xoffset); Serial.print(", ");
    Serial.print(_gyro_Yoffset); Serial.print(", ");
    Serial.println(_gyro_Zoffset);
    Serial.print("accl offsets [x, y, z]: ");
    Serial.print(_accl_Xoffset); Serial.print(", ");
    Serial.print(_accl_Yoffset); Serial.print(", ");
    Serial.println(_accl_Zoffset);
}

