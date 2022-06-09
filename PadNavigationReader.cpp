#include "PadNavigationReader.h"

PadNavigationReader::PadNavigationReader(uint8_t padUp, uint8_t padOk, uint8_t padDown) {
  this->m_PadUp = padUp;
  this->m_PadOk = padOk;
  this->m_PadDown = padDown;
}

void PadNavigationReader::init() {
  pinMode(this->m_PadUp, INPUT_PULLUP);
  pinMode(this->m_PadOk, INPUT_PULLUP);
  pinMode(this->m_PadDown, INPUT_PULLUP);
}

NavigationAction PadNavigationReader::read() {
  if (digitalRead(PIN_PAD_UP) == LOW) {
    while(digitalRead(PIN_PAD_UP) == LOW);
    return NAVIGATION_UP;
  }

  if (digitalRead(PIN_PAD_OK) == LOW) {
    while(digitalRead(PIN_PAD_OK) == LOW);
    return NAVIGATION_OK;
  }

  if (digitalRead(PIN_PAD_DOWN) == LOW) {
    while(digitalRead(PIN_PAD_DOWN) == LOW);
    return NAVIGATION_DOWN;
  }

  return NAVIGATION_NOTHING;
};