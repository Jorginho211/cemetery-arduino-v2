#ifndef PERIPHERALS_H
  #define PERIPHERALS_H

  #include <Arduino.h>
  #include <RTClib.h>
  #include <LiquidCrystal_I2C.h>
  #include "SoundPlayer.h"

  class Peripherals {
    public:
      void initLcd(uint8_t address, uint8_t width, uint8_t height);
      void initRtc();
      void initPinSystemState(uint8_t pin);
      void initPinLoudSpeakerState(uint8_t pin);
      void initPinDoorState(uint8_t pin);
      void initPinLedScheduleState(uint8_t pin);
      void initSoundPlayer(HardwareSerial &serial);

      bool getSystemState();
      bool getLoudSpeakerState();
      bool getIsDoorOpen();
      bool getLedScheduleState();

      void setLoudSpeakerState(bool state);
      void setDoorState(bool state);
      void setLedScheduleState(bool state);

      RTC_DS3231 Rtc;
      LiquidCrystal_I2C *Lcd;
      SoundPlayer SoundPlayer;
      bool m_IsDoorOpen; // Ñapa para o estado da porta
    private:
      uint8_t m_PinSystemState;
      uint8_t m_PinLedScheduleState;
      uint8_t m_PinLoudSpeakerState;
      uint8_t m_PinDoorState;

      bool m_LoudSpeakerState;
      bool m_LedScheduleState;
  };
#endif