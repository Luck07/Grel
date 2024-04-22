#include <Wire.h>

class MPU {	
private:
	float kalman_roll_u = 2*2;
	float kalman_pitch_u = 2*2;
	float kalman_1d_out[2] = {0, 0};

	void kalman_1d(float state, float unc, float input, float meas) {
		state = state + 0.004*input;
		unc = unc + 0.004*0.004*4*4;
		float gain = unc/(unc + 3*3);
		state = state + gain*(meas - state);
		unc = unc * (1 - gain);
		kalman_1d_out[0] = state;
		kalman_1d_out[1] = unc;
	}

public:

	void init() {
		Wire.setClock(400000);
		Wire.begin();
		delay(250);

		//power mode
		Wire.beginTransmission(0x68);
		Wire.write(0x6B);
		Wire.write(0x00);
		Wire.endTransmission();
	}

	void update() {
		// FILTRO PASSA BAIXA 
		/*  CFG BandWith AccDelay GyroDelay
		 * 0x00   260 Hz   0.0 ms   0.98 ms
		 * 0x01   184 Hz   2.0 ms    1.9 ms
		 * 0x02    94 Hz   3.0 ms    2.8 ms
		 * 0x03    44 Hz   4.9 ms    4.8 ms
		 * 0x04    21 Hz   8.5 ms    8.3 ms
		 * 0x05    10 Hz  13.8 ms   13.4 ms
		 * 0x06     5 Hz  19.8 ms   18.6 ms 
		*/
		Wire.beginTransmission(0x68); // i2c who am i
		Wire.write(0x1A); //config
		Wire.write(0x05); // 10hz
		Wire.endTransmission();

		// GYRO RANGE 
		/*   FS_SEL FullScaleRange LSB_sensitivity
		 * 0  (0x0)   +-  250 dg/s    131 LSB/dg/s
		 * 1  (0x8)   +-  500 dg/s   65.5 LSB/dg/s x
		 * 2 (0x10)   +- 1000 dg/s   32.8 LSB/dg/s
		 * 3 (0x18)   +- 2000 dg/s   16.4 LSB/dg/s
		*/
		Wire.beginTransmission(0x68); // i2c who am i
		Wire.write(0x1B); //config
		Wire.write(0x8); // +- 500 dg/s
		Wire.endTransmission();

		// ACC RANGE
		/*  AFS_SEL FullScaleRange LSB_sensitivity
		 * 0  (0x0)         +-  2g     16384 LSB/g
		 * 1  (0x8)         +-  4g      8192 LSB/g
		 * 2 (0x10)         +-  8g      4096 LSB/g x
		 * 3 (0x18)         +- 16g      2048 LSB/g
		*/
		Wire.beginTransmission(0x68); // i2c who am i
		Wire.write(0x1C); //config
		Wire.write(0x10); // +- 8g
		Wire.endTransmission();

		// fetch gyro
		Wire.beginTransmission(0x68);
		Wire.write(0x43); // gyro_xout
		Wire.endTransmission();
		Wire.requestFrom(0x68, 6);
		int16_t gyro_x = Wire.read()<<8 | Wire.read();
		int16_t gyro_y = Wire.read()<<8 | Wire.read();
		int16_t gyro_z = Wire.read()<<8 | Wire.read();

		// fetch acc
		Wire.beginTransmission(0x68);
		Wire.write(0x3B); // acc_xout
		Wire.endTransmission();
		Wire.requestFrom(0x68, 6);
		int16_t accX = Wire.read()<<8 | Wire.read();
		int16_t accY = Wire.read()<<8 | Wire.read();
		int16_t accZ = Wire.read()<<8 | Wire.read();	

		// convverte os valores ddo gyro pra dg/s
		roll_rate  = (float) gyro_x/65.5; // 65.5 LSB/dg/s
		pitch_rate = (float) gyro_y/65.5; 
		yaw_rate   = (float) gyro_z/65.5;

		// converte os valores do acc pra mltiplos de g (9.81 m/s^2)
		acc_x = (float) accX/4096; // 4096 LSB/g
		acc_y = (float) accY/4096; 
		acc_z = (float) accZ/4096; 
	}

	float get_rpy(float& r, float& p, float& y) {
		r = atan2(acc_y, sqrt( acc_x*acc_x + acc_z*acc_z )) * 180/M_PI;
		p = atan2(-acc_x, sqrt( acc_y*acc_y + acc_z*acc_z ))* 180/M_PI;
		y = atan2(sqrt( acc_x*acc_x + acc_y*acc_y ), acc_z) * 180/M_PI;
	}

	void kalman_update(float r, float p) {
		kalman_1d(kalman_roll, kalman_roll_u, roll_rate, r);
		kalman_roll = kalman_1d_out[0];
		kalman_roll_u = kalman_1d_out[1];
		kalman_1d(kalman_pitch, kalman_pitch_u, pitch_rate, p);
		kalman_pitch = kalman_1d_out[0];
		kalman_pitch_u = kalman_1d_out[1];
	}

public:
	float roll_rate, pitch_rate, yaw_rate;
	float acc_x, acc_y, acc_z;
	float kalman_roll = 0;
	float kalman_pitch = 0;
};

MPU mpu;

// calibracao por media
float roll_cal, pitch_cal, yaw_cal;
void calc_gyrocal(int t=2000) {
	for(int i=0; i<t; i++) {
		mpu.update();
		roll_cal  += mpu.roll_rate;
		pitch_cal += mpu.pitch_rate;
		yaw_cal   += mpu.yaw_rate;
		delay(1);
	}
	roll_cal  /= t;
	pitch_cal /= t;
	yaw_cal   /= t;
}

void setup() {
	Serial.begin(9600);
	mpu.init();

	Serial.println("calculando calibracoes calmou");
	//calc_gyrocal();
}

void loop() {
	mpu.update();

	// mpu.roll_rate  -= roll_cal;
	// mpu.pitch_rate -= pitch_cal;
	// mpu.yaw_rate   -= yaw_cal;

	float y, p, r;
	mpu.get_rpy(y, p, r);

	mpu.kalman_update(r, p);

	// dg/s
	Serial.print(mpu.roll_rate); Serial.print("/");
	Serial.print(mpu.pitch_rate); Serial.print("/");
	Serial.print(mpu.yaw_rate); Serial.print("\t");

	// g
	Serial.print(mpu.acc_x); Serial.print("/");
	Serial.print(mpu.acc_y); Serial.print("/"); 
	Serial.print(mpu.acc_z); Serial.print("\t");

	// dg
	Serial.print(r); Serial.print("/");
	Serial.print(p); Serial.print("/"); 
	Serial.print(y); Serial.print("\t");

	// dg
	Serial.print(mpu.kalman_roll); Serial.print("/"); 
	Serial.println(mpu.kalman_pitch); 
}
