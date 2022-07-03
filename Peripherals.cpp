#include "Peripherals.h"
#include "SIM900.h"

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

void Peripherals::initPinLedScheduleState(uint8_t pin) {
  this->m_PinLedScheduleState = pin;
  pinMode(this->m_PinLedScheduleState, OUTPUT);
  this->setLedScheduleState(false);
}

void Peripherals::initPinLoudSpeakerState(uint8_t pin) {
  this->m_PinLoudSpeakerState = pin;
  pinMode(this->m_PinLoudSpeakerState, OUTPUT);
  this->setLoudSpeakerState(false);
}

void Peripherals::initPinDoorState(uint8_t pin) {
  this->m_IsDoorOpen = false;
  this->m_PinDoorState = pin;
  pinMode(this->m_PinDoorState, OUTPUT);
  this->setDoorState(false);
}

void Peripherals::initSoundPlayer(HardwareSerial &serial) {
  this->SoundPlayer.init(serial);
}

void Peripherals::initNetworkAdapter(HardwareSerial &serial, String apn, String user, String password, uint16_t baudRate) {
  this->NetworkAdapter = new SIM900(apn, user, password, baudRate);
  this->NetworkAdapter->init(serial);
}

bool Peripherals::getSystemState() {
  return digitalRead(this->m_PinSystemState) == LOW;
}

bool Peripherals::getLedScheduleState() {
  return this->m_LedScheduleState;
}

bool Peripherals::getLoudSpeakerState() {
  return this->m_LoudSpeakerState;
}

bool Peripherals::getIsDoorOpen() {
  return this->m_IsDoorOpen;
}

void Peripherals::setLedScheduleState(bool state) {
  this->m_LedScheduleState = state;
  digitalWrite(this->m_PinLedScheduleState, !state);
}

void Peripherals::setLoudSpeakerState(bool state) {
  this->m_LoudSpeakerState = state;
  digitalWrite(this->m_PinLoudSpeakerState, !state);
}

void Peripherals::setDoorState(bool state) {
  digitalWrite(this->m_PinDoorState, !state);
}