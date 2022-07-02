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
      uint8_t getNumberOfFestives();
      DateTime getFestiveDate(uint8_t festiveIndex);

      void setWeekDays(uint8_t weekDays);
      void setOpenDoorTime(DateTime time);
      void setCloseDoorTime(DateTime time);
      void setLoudSpeakerTime(DateTime time);
      void setChangedSummerWinterTime(bool changedSummerWinterTime);
      void setNumberOfFestives(uint8_t numberOfFestives);
      void setFestiveDate(uint8_t festiveIndex, DateTime festiveDate);
    private:
      DataManager() = default;
      static DataManager instance;
  };
#endif