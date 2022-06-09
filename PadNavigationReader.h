#ifndef PAD_NAVIGATION_READER_H
  #define PAD_NAVIGATION_READER_H

  #define PIN_PAD_UP 23
  #define PIN_PAD_DOWN 25
  #define PIN_PAD_OK 27

  #include <Arduino.h>
  #include "NavigationReader.h"

  class PadNavigationReader: public NavigationReader {
    public:
      PadNavigationReader(uint8_t padUp, uint8_t padOk, uint8_t padDown);
      void init();
      NavigationAction read();
    private:
      uint8_t m_PadUp;
      uint8_t m_PadOk;
      uint8_t m_PadDown;
  };

#endif