#include "DataManager.h"

DataManager *DataManager::getInstance() {
  return &DataManager::instance;
}

uint8_t DataManager::getWeekDays() {
  return EEPROM.read(0);
}

void DataManager::setWeekDays(uint8_t weekDays) {
  EEPROM.write(0, weekDays);
}

DateTime DataManager::getOpenDoorTime() {
  return DateTime(0, 0, 0, EEPROM.read(3), EEPROM.read(4), 0);
}

void DataManager::setOpenDoorTime(DateTime openDoorTime) {
  EEPROM.write(3, openDoorTime.hour());
  EEPROM.write(4, openDoorTime.minute());
}

DateTime DataManager::getCloseDoorTime() {
  return DateTime(0, 0, 0, EEPROM.read(5), EEPROM.read(6), 0);
}

void DataManager::setCloseDoorTime(DateTime closeDoorTime) {
  EEPROM.write(5, closeDoorTime.hour());
  EEPROM.write(6, closeDoorTime.minute());
}

DateTime DataManager::getLoudSpeakerTime() {
  return DateTime(0, 0, 0, EEPROM.read(1), EEPROM.read(2), 0);
}

void DataManager::setLoudSpeakerTime(DateTime loudSpeakerTime) {
  EEPROM.write(1, loudSpeakerTime.hour());
  EEPROM.write(2, loudSpeakerTime.minute());
}

bool DataManager::getChangedSummerWinterTime() {
  return (bool) EEPROM.read(7);
}

void DataManager::setChangedSummerWinterTime(bool changedSummerWinterTime) {
  EEPROM.write(7, (uint8_t) changedSummerWinterTime);
}

// ----------------------------------------------------------------------------
// Deixanse os bytes 8 e 9 sen usar
// Reservanse os bytes do 10 ao 30 para a xestion de festivos

uint8_t DataManager::getNumberOfFestives() {
  return (uint8_t) EEPROM.read(10);
}

void DataManager::setNumberOfFestives(uint8_t numberOfFestives) {
  EEPROM.write(10, numberOfFestives);
}

DateTime DataManager::getFestiveDate(uint8_t festiveIndex) {
  uint8_t dayIndex = 12 + festiveIndex * 2;
  uint8_t monthIndex = dayIndex + 1;

  uint8_t year = EEPROM.read(11);
  uint8_t day = EEPROM.read(dayIndex);
  uint8_t month = EEPROM.read(monthIndex);

  int completeYear = 2000 + year; // Consideramos que las fechas empiezan en el año 2000
  return DateTime(year, month, day, 0, 0, 0);
}

void DataManager::setFestiveDate(uint8_t festiveIndex, DateTime festive) {
  uint8_t dayIndex = 12 + festiveIndex * 2;
  uint8_t monthIndex = dayIndex + 1;
  uint8_t year = festive.year() - 2000;

  if (festiveIndex == 0) {
    EEPROM.write(11, year);
  }

  EEPROM.write(dayIndex, festive.day());
  EEPROM.write(monthIndex, festive.month());
}
// ----------------------------------------------------------------------------