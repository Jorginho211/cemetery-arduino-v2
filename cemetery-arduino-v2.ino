#include "config.h"
#include "Peripherals.h"

#if NAVIGATION_SERIAL_ENABLED == 1
  #include "SerialNavigationReader.h"
  NavigationReader *m_NavigationReader = new SerialNavigationReader(NAVIGATION_SERIAL_BAUD);
#else if
  #include "PadNavigationReader.h"
  NavigationReader *m_NavigationReader = new PadNavigationReader(PIN_PAD_UP, PIN_PAD_OK, PIN_PAD_DOWN);
#endif

Peripherals m_Peripherals;

void setup() {
  m_NavigationReader->init();
  m_Peripherals.initRtc();
  m_Peripherals.initLcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
}

void loop() {
  NavigationAction action = m_NavigationReader->read();

  delay(16);
}
