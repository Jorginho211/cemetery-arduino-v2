#include "Peripherals.h"

void Peripherals::initLcd(uint8_t address, uint8_t columns, uint8_t rows) {
  this->Lcd = new LiquidCrystal_I2C(address, columns, rows);

  this->Lcd->begin(columns, rows);
  this->Lcd->clear();
}

void Peripherals::initRtc() {
  if (!this->Rtc.begin()) {
    Serial.println(F("Couldn't find RTC"));
    while(!this->Rtc.begin());
  }

  DateTime now = this->Rtc.now();
  Serial.println(now.year());
}