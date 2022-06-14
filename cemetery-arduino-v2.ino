#include "config.h"
#include "Peripherals.h"
#include "ViewsManager.h"
#include "ViewMain.h"

#if NAVIGATION_SERIAL_ENABLED == 1
  #include "SerialNavigationReader.h"
  NavigationReader *m_NavigationReader = new SerialNavigationReader(NAVIGATION_SERIAL_BAUD);
#else if
  #include "PadNavigationReader.h"
  NavigationReader *m_NavigationReader = new PadNavigationReader(PIN_PAD_UP, PIN_PAD_OK, PIN_PAD_DOWN);
#endif

Peripherals m_Peripherals;
ViewsManager m_ViewsManager;

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
  Serial.begin(9600);
  m_NavigationReader->init();
  m_Peripherals.initRtc();
  m_Peripherals.initLcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
  m_Peripherals.initPinSystemState(PIN_SWITCH_SYSTEM_STATE);
  m_Peripherals.initPinLoudSpeakerState(PIN_LOUD_SPEAKER);
  m_Peripherals.initPinDoorState(PIN_DOOR);
  m_Peripherals.initPinLedScheduleState(PIN_LED_SCHEDULE);

  m_ViewsManager.Peripherals = &m_Peripherals;
  m_ViewsManager.setCurrentView(new ViewMain(&m_ViewsManager));
}

void loop() {
  NavigationAction action = m_NavigationReader->read();
  
  m_ViewsManager.buttonPressed(action);
  m_ViewsManager.update(m_Peripherals.Rtc.now());
  m_ViewsManager.draw();
  
  delay(16);
}
