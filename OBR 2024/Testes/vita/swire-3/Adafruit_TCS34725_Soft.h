#ifndef _ADAFRUIT_TCS34725_SOFT_H
#define _ADAFRUIT_TCS34725_SOFT_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Adafruit_I2CDevice_Soft.h"

#define TCS34725_ADDRESS (0x29)     /**< I2C address **/
#define TCS34725_COMMAND_BIT (0x80) /**< Command bit **/
#define TCS34725_ENABLE (0x00)      /**< Interrupt Enable register */
#define TCS34725_ENABLE_AIEN (0x10) /**< RGBC Interrupt Enable */
#define TCS34725_ENABLE_WEN                                                    \
  (0x08) /**< Wait Enable - Writing 1 activates the wait timer */
#define TCS34725_ENABLE_AEN                                                    \
  (0x02) /**< RGBC Enable - Writing 1 actives the ADC, 0 disables it */
#define TCS34725_ENABLE_PON                                                    \
  (0x01) /**< Power on - Writing 1 activates the internal oscillator, 0        \
            disables it */
#define TCS34725_ATIME (0x01) /**< Integration time */
#define TCS34725_WTIME                                                         \
  (0x03) /**< Wait time (if TCS34725_ENABLE_WEN is asserted) */
#define TCS34725_WTIME_2_4MS (0xFF) /**< WLONG0 = 2.4ms   WLONG1 = 0.029s */
#define TCS34725_WTIME_204MS (0xAB) /**< WLONG0 = 204ms   WLONG1 = 2.45s  */
#define TCS34725_WTIME_614MS (0x00) /**< WLONG0 = 614ms   WLONG1 = 7.4s   */
#define TCS34725_AILTL                                                         \
  (0x04) /**< Clear channel lower interrupt threshold (lower byte) */
#define TCS34725_AILTH                                                         \
  (0x05) /**< Clear channel lower interrupt threshold (higher byte) */
#define TCS34725_AIHTL                                                         \
  (0x06) /**< Clear channel upper interrupt threshold (lower byte) */
#define TCS34725_AIHTH                                                         \
  (0x07) /**< Clear channel upper interrupt threshold (higher byte) */
#define TCS34725_PERS                                                          \
  (0x0C) /**< Persistence register - basic SW filtering mechanism for          \
            interrupts */
#define TCS34725_PERS_NONE                                                     \
  (0b0000) /**< Every RGBC cycle generates an interrupt */
#define TCS34725_PERS_1_CYCLE                                                  \
  (0b0001) /**< 1 clean channel value outside threshold range generates an     \
              interrupt */
#define TCS34725_PERS_2_CYCLE                                                  \
  (0b0010) /**< 2 clean channel values outside threshold range generates an    \
              interrupt */
#define TCS34725_PERS_3_CYCLE                                                  \
  (0b0011) /**< 3 clean channel values outside threshold range generates an    \
              interrupt */
#define TCS34725_PERS_5_CYCLE                                                  \
  (0b0100) /**< 5 clean channel values outside threshold range generates an    \
              interrupt */
#define TCS34725_PERS_10_CYCLE                                                 \
  (0b0101) /**< 10 clean channel values outside threshold range generates an   \
              interrupt*/
#define TCS34725_PERS_15_CYCLE                                                 \
  (0b0110) /**< 15 clean channel values outside threshold range generates an   \
              interrupt*/
#define TCS34725_PERS_20_CYCLE                                                 \
  (0b0111) /**< 20 clean channel values outside threshold range generates an   \
              interrupt*/
#define TCS34725_PERS_25_CYCLE                                                 \
  (0b1000) /**< 25 clean channel values outside threshold range generates an   \
              interrupt*/
#define TCS34725_PERS_30_CYCLE                                                 \
  (0b1001) /**< 30 clean channel values outside threshold range generates an   \
              interrupt*/
#define TCS34725_PERS_35_CYCLE                                                 \
  (0b1010) /**< 35 clean channel values outside threshold range generates an   \
              interrupt*/
#define TCS34725_PERS_40_CYCLE                                                 \
  (0b1011) /**< 40 clean channel values outside threshold range generates an   \
              interrupt*/
#define TCS34725_PERS_45_CYCLE                                                 \
  (0b1100) /**< 45 clean channel values outside threshold range generates an   \
              interrupt*/
#define TCS34725_PERS_50_CYCLE                                                 \
  (0b1101) /**< 50 clean channel values outside threshold range generates an   \
              interrupt*/
#define TCS34725_PERS_55_CYCLE                                                 \
  (0b1110) /**< 55 clean channel values outside threshold range generates an   \
              interrupt*/
#define TCS34725_PERS_60_CYCLE                                                 \
  (0b1111) /**< 60 clean channel values outside threshold range generates an   \
              interrupt*/
#define TCS34725_CONFIG (0x0D) /**< Configuration **/
#define TCS34725_CONFIG_WLONG                                                  \
  (0x02) /**< Choose between short and long (12x) wait times via               \
            TCS34725_WTIME */
#define TCS34725_CONTROL (0x0F) /**< Set the gain level for the sensor */
#define TCS34725_ID                                                            \
  (0x12) /**< 0x44 = TCS34721/TCS34725, 0x4D = TCS34723/TCS34727 */
#define TCS34725_STATUS (0x13)      /**< Device status **/
#define TCS34725_STATUS_AINT (0x10) /**< RGBC Clean channel interrupt */
#define TCS34725_STATUS_AVALID                                                 \
  (0x01) /**< Indicates that the RGBC channels have completed an integration   \
            cycle */
#define TCS34725_CDATAL (0x14) /**< Clear channel data low byte */
#define TCS34725_CDATAH (0x15) /**< Clear channel data high byte */
#define TCS34725_RDATAL (0x16) /**< Red channel data low byte */
#define TCS34725_RDATAH (0x17) /**< Red channel data high byte */
#define TCS34725_GDATAL (0x18) /**< Green channel data low byte */
#define TCS34725_GDATAH (0x19) /**< Green channel data high byte */
#define TCS34725_BDATAL (0x1A) /**< Blue channel data low byte */
#define TCS34725_BDATAH (0x1B) /**< Blue channel data high byte */

/** Integration time settings for TCS34725 */
/*
 * 60-Hz period: 16.67ms, 50-Hz period: 20ms
 * 100ms is evenly divisible by 50Hz periods and by 60Hz periods
 */
#define TCS34725_INTEGRATIONTIME_2_4MS                                         \
  (0xFF) /**< 2.4ms - 1 cycle - Max Count: 1024 */
#define TCS34725_INTEGRATIONTIME_24MS                                          \
  (0xF6) /**< 24.0ms - 10 cycles - Max Count: 10240 */
#define TCS34725_INTEGRATIONTIME_50MS                                          \
  (0xEB) /**< 50.4ms - 21 cycles - Max Count: 21504 */
#define TCS34725_INTEGRATIONTIME_60MS                                          \
  (0xE7) /**< 60.0ms - 25 cycles - Max Count: 25700 */
#define TCS34725_INTEGRATIONTIME_101MS                                         \
  (0xD6) /**< 100.8ms - 42 cycles - Max Count: 43008 */
#define TCS34725_INTEGRATIONTIME_120MS                                         \
  (0xCE) /**< 120.0ms - 50 cycles - Max Count: 51200 */
#define TCS34725_INTEGRATIONTIME_154MS                                         \
  (0xC0) /**< 153.6ms - 64 cycles - Max Count: 65535 */
#define TCS34725_INTEGRATIONTIME_180MS                                         \
  (0xB5) /**< 180.0ms - 75 cycles - Max Count: 65535 */
#define TCS34725_INTEGRATIONTIME_199MS                                         \
  (0xAD) /**< 199.2ms - 83 cycles - Max Count: 65535 */
#define TCS34725_INTEGRATIONTIME_240MS                                         \
  (0x9C) /**< 240.0ms - 100 cycles - Max Count: 65535 */
#define TCS34725_INTEGRATIONTIME_300MS                                         \
  (0x83) /**< 300.0ms - 125 cycles - Max Count: 65535 */
#define TCS34725_INTEGRATIONTIME_360MS                                         \
  (0x6A) /**< 360.0ms - 150 cycles - Max Count: 65535 */
#define TCS34725_INTEGRATIONTIME_401MS                                         \
  (0x59) /**< 400.8ms - 167 cycles - Max Count: 65535 */
#define TCS34725_INTEGRATIONTIME_420MS                                         \
  (0x51) /**< 420.0ms - 175 cycles - Max Count: 65535 */
#define TCS34725_INTEGRATIONTIME_480MS                                         \
  (0x38) /**< 480.0ms - 200 cycles - Max Count: 65535 */
#define TCS34725_INTEGRATIONTIME_499MS                                         \
  (0x30) /**< 499.2ms - 208 cycles - Max Count: 65535 */
#define TCS34725_INTEGRATIONTIME_540MS                                         \
  (0x1F) /**< 540.0ms - 225 cycles - Max Count: 65535 */
#define TCS34725_INTEGRATIONTIME_600MS                                         \
  (0x06) /**< 600.0ms - 250 cycles - Max Count: 65535 */
#define TCS34725_INTEGRATIONTIME_614MS                                         \
  (0x00) /**< 614.4ms - 256 cycles - Max Count: 65535 */

/** Gain settings for TCS34725  */
typedef enum {
  TCS34725_GAIN_1X = 0x00,  /**<  No gain  */
  TCS34725_GAIN_4X = 0x01,  /**<  4x gain  */
  TCS34725_GAIN_16X = 0x02, /**<  16x gain */
  TCS34725_GAIN_60X = 0x03  /**<  60x gain */
} tcs34725Gain_t;

/*!
 *  @brief  Class that stores state and functions for interacting with
 *          TCS34725 Color Sensor
 */
template <class WIRE_T>
class Adafruit_TCS34725 {
public:

  /*!
  *  @brief  Constructor
  *  @param  it
  *          Integration Time
  *  @param  gain
  *          Gain
  */
  Adafruit_TCS34725(uint8_t it = TCS34725_INTEGRATIONTIME_2_4MS,
                    tcs34725Gain_t gain = TCS34725_GAIN_1X) {
    _tcs34725Initialised = false;
    _tcs34725IntegrationTime = it;
    _tcs34725Gain = gain;
  }

  /*!
  *  @brief  Initializes I2C and configures the sensor
  *  @param  addr
  *          i2c address
  *  @param  *theWire
  *          The Wire object
  *  @return True if initialization was successful, otherwise false.
  */
  boolean begin(WIRE_T* theWire, uint8_t addr = TCS34725_ADDRESS) {
    if (i2c_dev)
      delete i2c_dev;
    i2c_dev = new Adafruit_I2CDevice<WIRE_T>(addr, theWire);

    return init();
  }

  /*!
  *  @brief  Part of begin
  *  @return True if initialization was successful, otherwise false.
  */
  boolean init() {
    if (!i2c_dev->begin()) {
      Serial.println("i2c_dev begin failed");
      return false;
    }

    /* Make sure we're actually connected */
    uint8_t x = read8(TCS34725_ID);
    if ((x != 0x4d) && (x != 0x44) && (x != 0x10)) {
      Serial.println("i2c_dev connection test failed");
      return false;
    }
    _tcs34725Initialised = true;

    /* Set default integration time and gain */
    setIntegrationTime(_tcs34725IntegrationTime);
    setGain(_tcs34725Gain);

    /* Note: by default, the device is in power down mode on bootup */
    enable();

    return true;
  }

  /*!
  *  @brief  Sets the integration time for the TC34725
  *  @param  it
  *          Integration Time
  */
  void setIntegrationTime(uint8_t it) {
    if (!_tcs34725Initialised) {
      Serial.println("ERRO setIntegrationTime(uint8_t) / TCS34725 NAO INICIALIZADO");
      return;
      //begin();
    }

    /* Update the timing register */
    write8(TCS34725_ATIME, it);

    /* Update value placeholders */
    _tcs34725IntegrationTime = it;
  }

  /*!
  *  @brief  Adjusts the gain on the TCS34725
  *  @param  gain
  *          Gain (sensitivity to light)
  */
  void setGain(tcs34725Gain_t gain) {
    if (!_tcs34725Initialised) {
      Serial.println("ERRO setGain(tcs34725Gain_t) / TCS34725 NAO INICIALIZADO");
      return;
      //begin();
    }

    /* Update the timing register */
    write8(TCS34725_CONTROL, gain);

    /* Update value placeholders */
    _tcs34725Gain = gain;
  }

  /*!
  *  @brief  Reads the raw red, green, blue and clear channel values
  *  @param  *r
  *          Red value
  *  @param  *g
  *          Green value
  *  @param  *b
  *          Blue value
  *  @param  *c
  *          Clear channel value
  */
  void getRawData(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c) {
    if (!_tcs34725Initialised) {
      Serial.println("ERRO getRawData(uint16_t*, uint16_t*, uint16_t*, uint16_t*) / TCS34725 NAO INICIALIZADO");
      return;
      //begin();
    }

    *c = read16(TCS34725_CDATAL);
    *r = read16(TCS34725_RDATAL);
    *g = read16(TCS34725_GDATAL);
    *b = read16(TCS34725_BDATAL);

    /* Set a delay for the integration time */
    /* 12/5 = 2.4, add 1 to account for integer truncation */
    delay((256 - _tcs34725IntegrationTime) * 12 / 5 + 1);
  }

  /*!
  *  @brief  Read the RGB color detected by the sensor.
  *  @param  *r
  *          Red value normalized to 0-255
  *  @param  *g
  *          Green value normalized to 0-255
  *  @param  *b
  *          Blue value normalized to 0-255
  */
  void getRGB(float *r, float *g, float *b) {
    uint16_t red, green, blue, clear;
    getRawData(&red, &green, &blue, &clear);
    uint32_t sum = clear;

    // Avoid divide by zero errors ... if clear = 0 return black
    if (clear == 0) {
      *r = *g = *b = 0;
      return;
    }

    *r = (float)red / sum * 255.0;
    *g = (float)green / sum * 255.0;
    *b = (float)blue / sum * 255.0;
  }

  /*!
  *  @brief  Reads the raw red, green, blue and clear channel values in
  *          one-shot mode (e.g., wakes from sleep, takes measurement, enters
  *          sleep)
  *  @param  *r
  *          Red value
  *  @param  *g
  *          Green value
  *  @param  *b
  *          Blue value
  *  @param  *c
  *          Clear channel value
  */
  void getRawDataOneShot(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c) {
    if (!_tcs34725Initialised) {
      Serial.println("ERRO getRawDataOneShot(uint16_t*, uint16_t*, uint16_t*, uint16_t*) / TCS34725 NAO INICIALIZADO");
      return;
      //begin();
    }

    enable();
    getRawData(r, g, b, c);
    disable();
  }

  /*!
  *  @brief  Converts the raw R/G/B values to color temperature in degrees Kelvin
  *  @param  r
  *          Red value
  *  @param  g
  *          Green value
  *  @param  b
  *          Blue value
  *  @return Color temperature in degrees Kelvin
  */
  uint16_t calculateColorTemperature(uint16_t r, uint16_t g, uint16_t b) {
    float X, Y, Z; /* RGB to XYZ correlation      */
    float xc, yc;  /* Chromaticity co-ordinates   */
    float n;       /* McCamy's formula            */
    float cct;

    if (r == 0 && g == 0 && b == 0) {
      return 0;
    }

    /* 1. Map RGB values to their XYZ counterparts.    */
    /* Based on 6500K fluorescent, 3000K fluorescent   */
    /* and 60W incandescent values for a wide range.   */
    /* Note: Y = Illuminance or lux                    */
    X = (-0.14282F * r) + (1.54924F * g) + (-0.95641F * b);
    Y = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
    Z = (-0.68202F * r) + (0.77073F * g) + (0.56332F * b);

    /* 2. Calculate the chromaticity co-ordinates      */
    xc = (X) / (X + Y + Z);
    yc = (Y) / (X + Y + Z);

    /* 3. Use McCamy's formula to determine the CCT    */
    n = (xc - 0.3320F) / (0.1858F - yc);

    /* Calculate the final CCT */
    cct =
        (449.0F * powf(n, 3)) + (3525.0F * powf(n, 2)) + (6823.3F * n) + 5520.33F;

    /* Return the results in degrees Kelvin */
    return (uint16_t)cct;
  }

  /*!
  *  @brief  Converts the raw R/G/B values to color temperature in degrees
  *          Kelvin using the algorithm described in DN40 from Taos (now AMS).
  *  @param  r
  *          Red value
  *  @param  g
  *          Green value
  *  @param  b
  *          Blue value
  *  @param  c
  *          Clear channel value
  *  @return Color temperature in degrees Kelvin
  */
  uint16_t calculateColorTemperature_dn40(uint16_t r, uint16_t g, uint16_t b,
                                          uint16_t c) {
    uint16_t r2, b2; /* RGB values minus IR component */
    uint16_t sat;    /* Digital saturation level */
    uint16_t ir;     /* Inferred IR content */

    if (c == 0) {
      return 0;
    }

    /* Analog/Digital saturation:
    *
    * (a) As light becomes brighter, the clear channel will tend to
    *     saturate first since R+G+B is approximately equal to C.
    * (b) The TCS34725 accumulates 1024 counts per 2.4ms of integration
    *     time, up to a maximum values of 65535. This means analog
    *     saturation can occur up to an integration time of 153.6ms
    *     (64*2.4ms=153.6ms).
    * (c) If the integration time is > 153.6ms, digital saturation will
    *     occur before analog saturation. Digital saturation occurs when
    *     the count reaches 65535.
    */
    if ((256 - _tcs34725IntegrationTime) > 63) {
      /* Track digital saturation */
      sat = 65535;
    } else {
      /* Track analog saturation */
      sat = 1024 * (256 - _tcs34725IntegrationTime);
    }

    /* Ripple rejection:
    *
    * (a) An integration time of 50ms or multiples of 50ms are required to
    *     reject both 50Hz and 60Hz ripple.
    * (b) If an integration time faster than 50ms is required, you may need
    *     to average a number of samples over a 50ms period to reject ripple
    *     from fluorescent and incandescent light sources.
    *
    * Ripple saturation notes:
    *
    * (a) If there is ripple in the received signal, the value read from C
    *     will be less than the max, but still have some effects of being
    *     saturated. This means that you can be below the 'sat' value, but
    *     still be saturating. At integration times >150ms this can be
    *     ignored, but <= 150ms you should calculate the 75% saturation
    *     level to avoid this problem.
    */
    if ((256 - _tcs34725IntegrationTime) <= 63) {
      /* Adjust sat to 75% to avoid analog saturation if atime < 153.6ms */
      sat -= sat / 4;
    }

    /* Check for saturation and mark the sample as invalid if true */
    if (c >= sat) {
      return 0;
    }

    /* AMS RGB sensors have no IR channel, so the IR content must be */
    /* calculated indirectly. */
    ir = (r + g + b > c) ? (r + g + b - c) / 2 : 0;

    /* Remove the IR component from the raw RGB values */
    r2 = r - ir;
    b2 = b - ir;

    if (r2 == 0) {
      return 0;
    }

    /* A simple method of measuring color temp is to use the ratio of blue */
    /* to red light, taking IR cancellation into account. */
    uint16_t cct = (3810 * (uint32_t)b2) / /** Color temp coefficient. */
                      (uint32_t)r2 +
                  1391; /** Color temp offset. */

    return cct;
  }

  /*!
  *  @brief  Converts the raw R/G/B values to lux
  *  @param  r
  *          Red value
  *  @param  g
  *          Green value
  *  @param  b
  *          Blue value
  *  @return Lux value
  */
  uint16_t calculateLux(uint16_t r, uint16_t g, uint16_t b) {
    float illuminance;

    /* This only uses RGB ... how can we integrate clear or calculate lux */
    /* based exclusively on clear since this might be more reliable?      */
    illuminance = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);

    return (uint16_t)illuminance;
  }

  /*!
  *  @brief  Writes a register and an 8 bit value over I2C
  *  @param  reg
  *  @param  value
  */
  void write8(uint8_t reg, uint8_t value) {
    uint8_t buffer[2] = {(uint8_t)(TCS34725_COMMAND_BIT | reg), value};
    i2c_dev->write(buffer, 2);
  }

  /*!
  *  @brief  Reads an 8 bit value over I2C
  *  @param  reg
  *  @return value
  */
  uint8_t read8(uint8_t reg) {
    uint8_t buffer[1] = {(uint8_t)(TCS34725_COMMAND_BIT | reg)};
    i2c_dev->write_then_read(buffer, 1, buffer, 1);
    return buffer[0];
  }

  /*!
  *  @brief  Reads a 16 bit values over I2C
  *  @param  reg
  *  @return value
  */
  uint16_t read16(uint8_t reg) {
    uint8_t buffer[2] = {(uint8_t)(TCS34725_COMMAND_BIT | reg), 0};
    i2c_dev->write_then_read(buffer, 1, buffer, 2);
    return (uint16_t(buffer[1]) << 8) | (uint16_t(buffer[0]) & 0xFF);
  }

  /*!
  *  @brief  Sets interrupt for TCS34725
  *  @param  i
  *          Interrupt (True/False)
  */
  void setInterrupt(boolean i) {
    uint8_t r = read8(TCS34725_ENABLE);
    if (i) {
      r |= TCS34725_ENABLE_AIEN;
    } else {
      r &= ~TCS34725_ENABLE_AIEN;
    }
    write8(TCS34725_ENABLE, r);
  }

  /*!
  *  @brief  Clears inerrupt for TCS34725
  */
  void clearInterrupt() {
    uint8_t buffer[1] = {TCS34725_COMMAND_BIT | 0x66};
    i2c_dev->write(buffer, 1);
  }

  /*!
  *  @brief  Sets inerrupt limits
  *  @param  low
  *          Low limit
  *  @param  high
  *          High limit
  */
  void setIntLimits(uint16_t low, uint16_t high) {
    write8(0x04, low & 0xFF);
    write8(0x05, low >> 8);
    write8(0x06, high & 0xFF);
    write8(0x07, high >> 8);
  }
  
  /*!
  *  @brief  Enables the device
  */
  void enable() {
    write8(TCS34725_ENABLE, TCS34725_ENABLE_PON);
    delay(3);
    write8(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
    /* Set a delay for the integration time.
      This is only necessary in the case where enabling and then
      immediately trying to read values back. This is because setting
      AEN triggers an automatic integration, so if a read RGBC is
      performed too quickly, the data is not yet valid and all 0's are
      returned */
    /* 12/5 = 2.4, add 1 to account for integer truncation */
    delay((256 - _tcs34725IntegrationTime) * 12 / 5 + 1);
  }

  /*!
  *  @brief  Disables the device (putting it in lower power sleep mode)
  */
  void disable() {
    uint8_t reg = 0;
    reg = read8(TCS34725_ENABLE);
    write8(TCS34725_ENABLE, reg & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN));
  }

private:
  Adafruit_I2CDevice<WIRE_T> *i2c_dev = NULL; ///< Pointer to I2C bus interface
  boolean _tcs34725Initialised;
  tcs34725Gain_t _tcs34725Gain;
  uint8_t _tcs34725IntegrationTime;

  float powf(const float x, const float y) {
    return (float)(pow((double)x, (double)y));
  }
};

#endif // _ADAFRUIT_TCS34725_SOFT_H