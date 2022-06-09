#include "SerialNavigationReader.h"

SerialNavigationReader::SerialNavigationReader(uint16_t baud) {
  this->m_Baud = baud;
}

void SerialNavigationReader::init() {
  Serial.begin(this->m_Baud);
}

NavigationAction SerialNavigationReader::read() {
  if (Serial.available()>0){
    char c = Serial.read();
    switch(c) {
      case 'a':
        return NAVIGATION_UP;
      case 's':
        return NAVIGATION_OK;
      case 'd':
        return NAVIGATION_DOWN;
    }
  }

  return NAVIGATION_NOTHING;
};