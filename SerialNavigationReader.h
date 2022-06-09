#ifndef SERIAL_NAVIGATION_READER_H
  #define SERIAL_NAVIGATION_READER_H

  #include <Arduino.h>
  #include "NavigationReader.h"

  class SerialNavigationReader: public NavigationReader {
    public:
      SerialNavigationReader(uint16_t baud);
      void init();
      NavigationAction read();
    private:
      uint16_t m_Baud;
  };

#endif