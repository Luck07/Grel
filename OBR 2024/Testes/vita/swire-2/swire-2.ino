#include <Wire.h>

#include "Adafruit_TCS34725_SoftWire.h"
#include "I2C_old.h"

//#define OI

#ifdef OI
#include <SoftwareWire.h>
#define SOFT SoftwareWire
#else
#include <SoftWire.h>
#define SOFT SoftWire
#endif

//#include "Adafruit_I2CDevice_SoftWire.h"

//#include <Adafruit_TCS34725_SWwire.h>

//SoftwareWire swWire(6, 7);
SOFT sWire(6, 7);

//Adafruit_I2CDevice_Soft _real_i2c = Adafruit_I2CDevice_Soft(&Wire, TCS34725_ADDRESS);

//Adafruit_I2CDevice<TwoWire>      real_i2c     = Adafruit_I2CDevice<TwoWire>(&Wire, TCS34725_ADDRESS);
//Adafruit_I2CDevice<SoftwareWire> SWW_soft_i2c = Adafruit_I2CDevice<SoftwareWire>(0x29, &swWire);
//Adafruit_I2CDevice<SoftWire>     SW_soft_i2c  = Adafruit_I2CDevice<SoftWire>(TCS34725_ADDRESS, &sWire);

Adafruit_TCS34725<TwoWire>      tcs_real     = Adafruit_TCS34725<TwoWire>(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725<SOFT> tcs_software = Adafruit_TCS34725<SOFT>(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
// Adafruit_TCS34725<SoftWire>   tcs_soft     = Adafruit_TCS34725<SoftWire>(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

void setup() {
  Serial.begin(9600);

  // if(real_i2c.begin())
  //   Serial.println("i2c real");
  // else
  //   Serial.println("sem real");

  // if(_real_i2c.begin())
  //   Serial.println("_i2c real");
  // else
  //   Serial.println("sem real");

  // Serial.println("--------------------");

  // uint8_t buffer[1] = {(uint8_t)(TCS34725_COMMAND_BIT | TCS34725_ID)};
  // real_i2c.write_then_read(buffer, 1, buffer, 1);
  // Serial.print("buffer 0 ");
  // Serial.println(buffer[0]);
  // Serial.print("buffer 1 ");
  // Serial.println(buffer[1]);

  // uint8_t _buffer[1] = {(uint8_t)(TCS34725_COMMAND_BIT | TCS34725_ID)};
  // _real_i2c.write_then_read(_buffer, 1, _buffer, 1);
  // Serial.print("_buffer 0 ");
  // Serial.println(_buffer[0]);
  // Serial.print("_buffer 1 ");
  // Serial.println(_buffer[1]);

  Serial.println("-");
  Serial.print("(real)");
  while(!tcs_real.begin(TCS34725_ADDRESS, &Wire)) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("found");

  Serial.print("(soft)");
  while(!tcs_software.begin(TCS34725_ADDRESS, &sWire)) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("found");


  //soft_tcs.begin(0, &sWire);
}

void loop() {
  uint16_t r1, g1, b1, c1, colorTemp1, lux1;
  uint16_t r2, g2, b2, c2, colorTemp2, lux2;

  tcs_real.getRawData(&r1, &g1, &b1, &c1);
  tcs_software.getRawData(&r2, &g2, &b2, &c2);

  Serial.print("REAL: ");
  Serial.print(r1, DEC); Serial.print("/");
  Serial.print(g1, DEC); Serial.print("/");
  Serial.print(b1, DEC); Serial.print("\t");

  Serial.print("SOFT: ");
  Serial.print(r2, DEC); Serial.print("/");
  Serial.print(g2, DEC); Serial.print("/");
  Serial.println(b2, DEC);
}