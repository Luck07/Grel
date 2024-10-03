#ifndef Adafruit_I2CDevice_SW_h
#define Adafruit_I2CDevice_SW_h

#include <Arduino.h>
#include <Wire.h>
#include <SoftwareWire.h>

///< The class which defines how we will talk to this device over I2C

#define WIRE_TYPE_REAL 0
#define WIRE_TYPE_SOFT 1

//template <typename WIRE_T>
class Adafruit_I2CDevice_Soft {
public:
  //Adafruit_I2CDevice_Soft(WIRE_T* theWire, uint8_t addr);
  Adafruit_I2CDevice_Soft(TwoWire* theWire, uint8_t addr);
  Adafruit_I2CDevice_Soft(SoftwareWire* theWire, uint8_t addr);

  uint8_t address(void);
  bool begin(bool addr_detect = true);
  void end(void);
  bool detected(void);

  bool read(uint8_t *buffer, size_t len, bool stop = true);
  bool write(const uint8_t *buffer, size_t len, bool stop = true,
             const uint8_t *prefix_buffer = nullptr, size_t prefix_len = 0);
  bool write_then_read(const uint8_t *write_buffer, size_t write_len,
                       uint8_t *read_buffer, size_t read_len,
                       bool stop = false);
  bool setSpeed(uint32_t desiredclk);

  /*!   @brief  How many bytes we can read in a transaction
   *    @return The size of the Wire receive/transmit buffer */
  size_t maxBufferSize() { return _maxBufferSize; }

private:
  uint8_t _addr;
  //WIRE_T* _wire;
  bool _wire_type;
  TwoWire *_wire;
  SoftwareWire* _softwire;
  bool _begun;
  size_t _maxBufferSize;
  bool _read(uint8_t *buffer, size_t len, bool stop);
};

#endif // Adafruit_I2CDevice_h