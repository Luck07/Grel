//#include <Adafruit_TCS34725.h>
#include <SoftwareWire.h>
#include <Wire.h>

#include "Adafruit_I2CDevice_SWwire.h"
#include "Adafruit_TCS34725_SWwire.h"
//#include "a.h"


/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */

SoftwareWire sWire(8, 9);

Adafruit_TCS34725_SWwire tcs_soft = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725_SWwire tcs_real = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

//Adafruit_TCS34725_SWwire<SoftwareWire> tcs_soft();
//Adafruit_TCS34725_SWwire<TwoWire>      tcs_real();

//tcs_soft tcs1 = tcs_soft(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
//Adafruit_TCS34725 tcs2 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

void setup(void) {
  Serial.begin(9600);

  if(tcs_soft.begin(&sWire, TCS34725_ADDRESS)) {
    Serial.println("Found sensor (soft)");
  } else {
    Serial.println("No TCS34725 found (soft)");
  }

  if(tcs_real.begin(&Wire, TCS34725_ADDRESS)) {
    Serial.println("Found sensor (real)");
  } else {
    Serial.println("No TCS34725 found (real)");
  }

  // Now we're ready to get readings!
}

void loop(void) {
  uint16_t r1, g1, b1, c1, colorTemp1, lux1;
  uint16_t r2, g2, b2, c2, colorTemp2, lux2;

  tcs_real.getRawData(&r1, &g1, &b1, &c1);
  tcs_soft.getRawData(&r2, &g2, &b2, &c2);

  Serial.print("REAL: ");
  Serial.print(r1, DEC); Serial.print("/");
  Serial.print(g1, DEC); Serial.print("/");
  Serial.print(b1, DEC); Serial.print("\t");

  Serial.print("SOFT: ");
  Serial.print(r2, DEC); Serial.print("/");
  Serial.print(g2, DEC); Serial.print("/");
  Serial.println(b2, DEC);

  // Serial.print("R1:"); Serial.print(r, DEC); Serial.print(",");
  // Serial.print("G1:"); Serial.print(g, DEC); Serial.print(",");
  // Serial.print("B1:"); Serial.print(b, DEC); Serial.print(",\t");

  // Serial.print("R2:"); Serial.print(r2, DEC); Serial.print(",");
  // Serial.print("G2:"); Serial.print(g2, DEC); Serial.print(",");
  // Serial.print("B2:"); Serial.print(b2, DEC); Serial.println(",");

}