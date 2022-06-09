#include "Peripherals.h"

void Peripherals::initLcd(uint8_t address, uint8_t columns, uint8_t rows) {
  this->Lcd = new LiquidCrystal_I2C(address, columns, rows);

  this->Lcd->begin(columns, rows);
  this->Lcd->backlight();
  this->Lcd->clear();
}

void Peripherals::initRtc() {
  if (!this->Rtc.begin()) {
    Serial.println(F("Couldn't find RTC"));
    while(!this->Rtc.begin());
  }

  if (this->Rtc.lostPower()) {
    this->Rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  DateTime now = this->Rtc.now();
}

void Peripherals::initPinSystemState(uint8_t pin) {
  this->m_PinSystemState = pin;
  pinMode(this->m_PinSystemState, INPUT_PULLUP);
}

bool Peripherals::getSystemState() {
  return digitalRead(this->m_PinSystemState) == LOW;
}