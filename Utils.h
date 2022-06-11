#ifndef UTILS_H
  #define UTILS_H

  #include <Arduino.h>
  #include <RTClib.h>

  enum DateTimeOperation {
    DATETIME_INCREASE = 0,
    DATETIME_DECREASE = 1
  };

  enum DateTimeSection {
    DATETIME_SECTION_DAY = 0,
    DATETIME_SECTION_MONTH = 1,
    DATETIME_SECTION_YEAR = 2,
    DATETIME_SECTION_HOUR = 3,
    DATETIME_SECTION_MINUTE = 4,
    DATETIME_SECTION_SECOND = 5    
  };

  class Utils {
    public:
      static String format00Number(unsigned int number) {
        if(number > 9)
          return String(number);
        
        return "0" + String(number);
      }

      static DateTime modifyDateTime(DateTime dateTime, DateTimeOperation operation, DateTimeSection section) {
        if (operation == DATETIME_DECREASE) {
          switch(section) {
            case DATETIME_SECTION_DAY:
              if(dateTime.day() > 1)
                dateTime = DateTime(dateTime.year(), dateTime.month(), dateTime.day() - 1, dateTime.hour(), dateTime.minute(), dateTime.second()); 
              break;
            case DATETIME_SECTION_MONTH:
              if (dateTime.month() > 1)
                dateTime = DateTime(dateTime.year(), dateTime.month() - 1, dateTime.day(), dateTime.hour(), dateTime.minute(), dateTime.second()); 
              break;
            case DATETIME_SECTION_YEAR:
              if(dateTime.year() > 2018)
                dateTime = DateTime(dateTime.year() - 1, dateTime.month(), dateTime.day(), dateTime.hour(), dateTime.minute(), dateTime.second());
              break; 
            case DATETIME_SECTION_HOUR:
              if (dateTime.hour() > 0)
                dateTime = DateTime(dateTime.year(), dateTime.month(), dateTime.day(), dateTime.hour() - 1, dateTime.minute(), dateTime.second()); 
              else
                dateTime = DateTime(dateTime.year(), dateTime.month(), dateTime.day(), 23, dateTime.minute(), dateTime.second()); 
              break;
            case DATETIME_SECTION_MINUTE:
              if(dateTime.minute() > 0)
                dateTime = DateTime(dateTime.year(), dateTime.month(), dateTime.day(), dateTime.hour(), dateTime.minute() - 1, dateTime.second()); 
              else
                dateTime = DateTime(dateTime.year(), dateTime.month(), dateTime.day(), dateTime.hour(), 59, dateTime.second()); 
              break;
            case DATETIME_SECTION_SECOND:
              if(dateTime.second() > 0)
                dateTime = DateTime(dateTime.year(), dateTime.month(), dateTime.day(), dateTime.hour(), dateTime.minute(), dateTime.second() - 1); 
              else
                dateTime = DateTime(dateTime.year(), dateTime.month(), dateTime.day(), dateTime.hour(), dateTime.minute(), 59); 
              break;
          }
        }
        else if (operation == DATETIME_INCREASE) {
          switch(section) {
            case DATETIME_SECTION_DAY:
              Serial.println(dateTime.day());
              if (dateTime.day() < 31) {
                dateTime = DateTime(dateTime.year(), dateTime.month(), dateTime.day() + 1, dateTime.hour(), dateTime.minute(), dateTime.second()); 
                Serial.println(dateTime.day());
              }
              break;
            case DATETIME_SECTION_MONTH:
              if(dateTime.month() < 12)
                dateTime = DateTime(dateTime.year(), dateTime.month() + 1, dateTime.day(), dateTime.hour(), dateTime.minute(), dateTime.second()); 
              break;
            case DATETIME_SECTION_YEAR:
              dateTime = DateTime(dateTime.year() + 1, dateTime.month(), dateTime.day(), dateTime.hour(), dateTime.minute(), dateTime.second()); 
              break;
            case DATETIME_SECTION_HOUR:
              if(dateTime.hour() < 23)
                dateTime = DateTime(dateTime.year(), dateTime.month(), dateTime.day(), dateTime.hour() + 1, dateTime.minute(), dateTime.second()); 
              else
                dateTime = DateTime(dateTime.year(), dateTime.month(), dateTime.day(), 0, dateTime.minute(), dateTime.second()); 
              break;
            case DATETIME_SECTION_MINUTE:
              if(dateTime.minute() < 59)
                dateTime = DateTime(dateTime.year(), dateTime.month(), dateTime.day(), dateTime.hour(), dateTime.minute() + 1, dateTime.second()); 
              else
                dateTime = DateTime(dateTime.year(), dateTime.month(), dateTime.day(), dateTime.hour(), 0, dateTime.second());
              break;
            case DATETIME_SECTION_SECOND:
              if(dateTime.second() < 59)
                dateTime = DateTime(dateTime.year(), dateTime.month(), dateTime.day(), dateTime.hour(), dateTime.minute(), dateTime.second() + 1); 
              else
                dateTime = DateTime(dateTime.year(), dateTime.month(), dateTime.day(), dateTime.hour(), dateTime.minute(), 0); 
              break;
          }
        }

        return dateTime;
      }
  };
#endif