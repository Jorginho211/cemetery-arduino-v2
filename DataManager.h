#ifndef DATA_H
  #define DATA_H

  #include <Arduino.h>
  #include <EEPROM.h>
  #include <RTClib.h>

  class DataManager {
    public:
      static DataManager *getInstance();  
      void load();

      uint8_t getWeekDays();
      DateTime getOpenDoorTime();
      DateTime getCloseDoorTime();
      DateTime getLoudSpeakerTime();
      bool getChangedSummerWinterTime();

      void setWeekDays(uint8_t weekDays);
      void setOpenDoorTime(DateTime time);
      void setCloseDoorTime(DateTime time);
      void setLoudSpeakerTime(DateTime time);
      void setChangedSummerWinterTime(bool changedSummerWinterTime);
    private:
      DataManager() = default;
      static DataManager instance;
  };
#endif