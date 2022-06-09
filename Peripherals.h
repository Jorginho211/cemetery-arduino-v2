#ifndef PERIPHERALS_H
  #define PERIPHERALS_H

  #include <Arduino.h>
  #include <RTClib.h>
  #include <LiquidCrystal_I2C.h>

  class Peripherals {
    public:
      void initLcd(uint8_t address, uint8_t width, uint8_t height);
      void initRtc();
      void initPinSystemState(uint8_t pin);
      bool getSystemState();

      RTC_DS3231 Rtc;
      LiquidCrystal_I2C *Lcd;
    private:
      uint8_t m_PinSystemState;
  };
#endif