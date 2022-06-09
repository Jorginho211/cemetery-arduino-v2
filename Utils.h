#ifndef UTILS_H
  #define UTILS_H

  #include <Arduino.h>

  class Utils {
    public:
      static String format00Number(unsigned int number) {
        if(number > 9)
          return String(number);
        
        return "0" + String(number);
      }
  };
#endif