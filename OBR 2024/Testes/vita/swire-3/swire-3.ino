#include <Wire.h>

#include "Adafruit_TCS34725_Soft.h"
#include <SoftwareWire.h>
#include <SoftWire.h>

SoftwareWire swWire(6, 7);
SoftWire sWire(6, 7);

Adafruit_I2CDevice<TwoWire>      i2c_real     = Adafruit_I2CDevice<TwoWire>(TCS34725_ADDRESS, &Wire);
Adafruit_I2CDevice<SoftWire>     i2c_soft     = Adafruit_I2CDevice<SoftWire>(TCS34725_ADDRESS, &sWire);
Adafruit_I2CDevice<SoftwareWire> i2c_software = Adafruit_I2CDevice<SoftwareWire>(TCS34725_ADDRESS, &swWire);

Adafruit_TCS34725<TwoWire>      tcs_real     = Adafruit_TCS34725<TwoWire>(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725<SoftWire>     tcs_soft     = Adafruit_TCS34725<SoftWire>(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725<SoftwareWire> tcs_software = Adafruit_TCS34725<SoftwareWire>(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

void setup(void) {
  Serial.begin(9600);

  sWire.setTimeout_ms(40);
  sWire.begin();
  sWire.setTimeout_ms(200);

  Serial.println("-");
  Serial.print("(real)-i2c-");
  while(!i2c_real.begin()) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("found");

  Serial.print("(software)-i2c-");
  while(!i2c_software.begin()) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("found");

  Serial.print("(soft)-i2c-");
  while(!i2c_soft.begin()) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("found");

  Serial.println("---");

  Serial.print("(real)-tcs-");
  while(!tcs_real.begin(&Wire)) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("found");

  Serial.print("(software)-tcs-");
  while(!tcs_software.begin(&swWire)) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("found");

  Serial.print("(soft)-tcs-");
  while(!tcs_soft.begin(&sWire)) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("found");


  // Now we're ready to get readings!
}

void loop(void) {
  // uint16_t r1, g1, b1, c1, colorTemp1, lux1;
  // uint16_t r2, g2, b2, c2, colorTemp2, lux2;

  // tcs_real.getRawData(&r1, &g1, &b1, &c1);
  // tcs_soft.getRawData(&r2, &g2, &b2, &c2);

  // Serial.print("(r/g/b) REAL: ");
  // Serial.print(r1, DEC); Serial.print("/");
  // Serial.print(g1, DEC); Serial.print("/");
  // Serial.print(b1, DEC); Serial.print("\t");

  // Serial.print("SOFT: ");
  // Serial.print(r2, DEC); Serial.print("/");
  // Serial.print(g2, DEC); Serial.print("/");
  // Serial.println(b2, DEC);
}