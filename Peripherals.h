#ifndef PERIPHERALS_H
  #define PERIPHERALS_H

  #include <Arduino.h>
  #include <RTClib.h>
  #include <LiquidCrystal_I2C.h>

  class Peripherals {
    public:
      void initLcd(uint8_t address, uint8_t width, uint8_t height);
      void initRtc();

      RTC_DS3231 Rtc;
      LiquidCrystal_I2C *Lcd;
  };
#endif