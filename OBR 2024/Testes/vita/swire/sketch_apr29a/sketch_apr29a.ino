#include <SoftwareWire.h>
#include <Adafruit_TCS34725.h>
#include "a.h"

#include <Wire.h>

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */

SoftwareWire sWire(8, 9);


tcs_soft tcs1 = tcs_soft(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcs2 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

void setup(void) {
  Serial.begin(9600);

  if (tcs1.begin(&sWire, TCS34725_ADDRESS)) {
    Serial.println("Found sensor(software)");
  } else {
    Serial.println("No TCS34725 found ... check your connections(software)");
    while (1);
  }

  if (tcs2.begin()) {
    Serial.println("Found sensor(normal)");
  } else {
    Serial.println("No TCS34725 found ... check your connections(normal)");
    while (1);
  }

  // Now we're ready to get readings!
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;
  uint16_t r2, g2, b2, c2, colorTemp2, lux2;

  tcs1.getRawData(&r, &g, &b, &c);
  tcs2.getRawData(&r2, &g2, &b2, &c2);


  Serial.print("R1:"); Serial.print(r, DEC); Serial.print(",");
  Serial.print("G1:"); Serial.print(g, DEC); Serial.print(",");
  Serial.print("B1:"); Serial.print(b, DEC); Serial.print(",\t");

  Serial.print("R2:"); Serial.print(r2, DEC); Serial.print(",");
  Serial.print("G2:"); Serial.print(g2, DEC); Serial.print(",");
  Serial.print("B2:"); Serial.print(b2, DEC); Serial.println(",");

}
