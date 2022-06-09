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