#include <Wire.h>

#include <SoftwareWire.h>
#include <SoftWire.h>

#include "Adafruit_I2CDevice.h"
#include "Adafruit_TCS34725.h"

SoftwareWire swWire(1, 2);
SoftWire sWire(3, 4);

Adafruit_I2CDevice<TwoWire>      real_i2c     = Adafruit_I2CDevice<TwoWire>(0, &Wire);
Adafruit_I2CDevice<SoftwareWire> SWW_soft_i2c = Adafruit_I2CDevice<SoftwareWire>(0, &swWire);
Adafruit_I2CDevice<SoftWire>     SW_soft_i2c  = Adafruit_I2CDevice<SoftWire>(0, &sWire);

Adafruit_TCS34725<TwoWire>      real_tcs     = Adafruit_TCS34725<TwoWire>(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725<SoftwareWire> SWW_soft_tcs = Adafruit_TCS34725<SoftwareWire>(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725<SoftWire>     SW_soft_tcs  = Adafruit_TCS34725<SoftWire>(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

void setup() {
  Serial.begin(9600);

  real_i2c.begin();
  SWW_soft_i2c.begin();
  SW_soft_i2c.begin();

  real_tcs.begin(0, &Wire);
  SWW_soft_tcs.begin(0, &swWire);
  SW_soft_tcs.begin(0, &sWire);
}

void loop() {
  
}