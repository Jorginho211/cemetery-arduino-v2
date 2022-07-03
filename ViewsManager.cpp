#include "ViewsManager.h"

void ViewsManager::buttonPressed(NavigationAction pressed) {
  this->m_CurrentView->buttonPressed(pressed);
}

void ViewsManager::update(DateTime now) {
  this->m_CurrentView->update(now);
}

void ViewsManager::draw() {
  this->m_CurrentView->draw();
}

void ViewsManager::setCurrentView(View *view) {
  if (this->m_CurrentView != nullptr)
    delete this->m_CurrentView;
    
  this->m_CurrentView = view;
}

void ViewsManager::mainTask(DateTime now) {
  this->checkChangeSummerWinterTime(now);
  this->checkOpenCloseDoor(now);
}

void ViewsManager::checkChangeSummerWinterTime(DateTime now) {
  DataManager *dataManager = DataManager::getInstance();

  bool isLastMarchSunday = now.month() == 3 && now.dayOfTheWeek() == 0 && (now.day() + 7) > 31 && now.hour() == 3 && now.minute() == 0;
  bool isLastOctoberSunday = now.month() == 10 && now.dayOfTheWeek() == 0 && (now.day() + 7) > 31 && now.hour() == 3 && now.minute() == 0;

  if(!dataManager->getChangedSummerWinterTime() && (isLastMarchSunday || isLastOctoberSunday)){
    uint8_t newHour = now.hour() + 1;
    if(isLastOctoberSunday)
      newHour = now.hour() - 1;

    this->Peripherals->Rtc.adjust(DateTime(now.year(), now.month(), now.day(), newHour, now.minute(), now.second()));
    dataManager->setChangedSummerWinterTime(true);
  }
  else if(now.dayOfTheWeek() == 1 && dataManager->getChangedSummerWinterTime()){
    dataManager->setChangedSummerWinterTime(false);
  }
}

void ViewsManager::checkOpenCloseDoor(DateTime now) {
  DataManager *dataManager = DataManager::getInstance();


  // Se esta en modo manual desabilitase todo
  if(!this->Peripherals->getSystemState()) {
    this->Peripherals->SoundPlayer.stop();
    this->Peripherals->setLedScheduleState(false);
    this->Peripherals->setLoudSpeakerState(false);
    this->Peripherals->setDoorState(false);
    return;
  }    

  bool isDayNotOpenDoor = (dataManager->getWeekDays() >> now.dayOfTheWeek()) & 0x01;
  if(!isDayNotOpenDoor) {
    if (this->Peripherals->getIsDoorOpen()) {
      this->performOpenCloseTask(false);
    }
    return;
  }

  // Conversion de tempos a minutos
  unsigned int currentMinutes = now.hour() * 60 + now.minute();
  unsigned int openDoorMinutes = dataManager->getOpenDoorTime().hour() * 60 + dataManager->getOpenDoorTime().minute();
  unsigned int closeDoorMinutes = dataManager->getCloseDoorTime().hour() * 60 + dataManager->getCloseDoorTime().minute();
  unsigned int loudSpeakerMinutes = dataManager->getLoudSpeakerTime().hour() * 60 + dataManager->getLoudSpeakerTime().minute();
  
  int differenceOpenDoorNow = openDoorMinutes - currentMinutes;
  int differenceCloseDoorNow = closeDoorMinutes - currentMinutes;

  bool isInSchedule = differenceOpenDoorNow <= 0 && differenceCloseDoorNow > 0;

  // Operacions para ver se necesitamos abrir ou pechar o portal
  if(!this->Peripherals->getIsDoorOpen() && isInSchedule){
    this->performOpenCloseTask(true);
  }
  else if(this->Peripherals->getIsDoorOpen() && !isInSchedule){
    this->performOpenCloseTask(false);
  }

  // Led que esta en horario de entrada
  this->Peripherals->setLedScheduleState(isInSchedule);

  // Operacions para saber se temos que poñer a megafonia a funcionar avisando do peche
  int differenceLoudSpeakerNow = loudSpeakerMinutes - currentMinutes;
  bool needToPlayLoudSpeaker = differenceLoudSpeakerNow <= 0 && differenceCloseDoorNow > 0;
  if(!this->Peripherals->getLoudSpeakerState() && needToPlayLoudSpeaker) {
    this->performLoudSpeakerTask(true);
  }
  else if(this->Peripherals->getLoudSpeakerState()){
    Serial.println("FUERA");
    this->performLoudSpeakerTask(false);
  }
}

void ViewsManager::performOpenCloseTask(bool isOpenProcess) {
  unsigned long currentMillis = millis();
  unsigned long lastDifferenceMillis = currentMillis - this->m_LastPerformOpenCloseTaskMillis;
  bool isPerformingTask = this->m_LastPerformOpenCloseTaskMillis > 0;

  if(!isPerformingTask) { 
    this->m_LastPerformOpenCloseTaskMillis = currentMillis;
    this->Peripherals->setDoorState(true);
    this->Peripherals->setLoudSpeakerState(false);
  }
  else if (isPerformingTask && lastDifferenceMillis >= 3000) { // Deixamos 3 segundos
    this->m_LastPerformOpenCloseTaskMillis = 0;
    this->Peripherals->setDoorState(false);
    this->Peripherals->m_IsDoorOpen = isOpenProcess;
  }
}

void ViewsManager::performLoudSpeakerTask(bool startingLoudSpeaker) {
  unsigned long currentMillis = millis();

  if(startingLoudSpeaker) {
    Serial.println("AQU2");
    this->Peripherals->setLoudSpeakerState(true);
    delay(10);
    this->Peripherals->SoundPlayer.play(1);
    this->m_LastPerformLoudSpeakerTaskMillis = currentMillis;
    return;
  }

  unsigned long lastDifferenceMillis = currentMillis - this->m_LastPerformLoudSpeakerTaskMillis;

  bool isPlaying = this->Peripherals->SoundPlayer.isPlaying();
  Serial.println(lastDifferenceMillis);
  if(!isPlaying && lastDifferenceMillis >= 5 * 60 * 1000) { // Repetir cada 5 min despues de que ha acabado
    Serial.println("AQU4");
    this->Peripherals->SoundPlayer.play(1);  
  }
  else if (isPlaying) {
    Serial.println("AQU5");
    this->m_LastPerformLoudSpeakerTaskMillis = currentMillis;
  }
}

bool ViewsManager::syncFestives() {
  Response ret = this->Peripherals->NetworkAdapter->get(URL_GET_FESTIVES);
  if(!ret.success || ret.status != 200)
    return false;

  // Exemplo de ret.content: 
  // 2201010601140415041705260524062507150812100111111106120812 
  // Indices 0-1 representa o ano
  // Resto de indices son dia e mes: ddmmddmmddmm....

  int year = 2000 + ret.content.substring(0, 2).toInt();
  String daysMonths = ret.content.substring(2);
  uint8_t totalFestives = daysMonths.length() / 4; // Cada festivo esta formado por 4 caracteres

  DataManager *dataManager = DataManager::getInstance();
  dataManager->setNumberOfFestives(totalFestives);

  uint8_t numberOfFestive = 0;
  for(uint8_t i = 0; i < daysMonths.length(); i += 4) {
    uint8_t day = daysMonths.substring(i, i + 2).toInt();
    uint8_t month = daysMonths.substring(i + 2, i + 4).toInt();

    DateTime festive = DateTime(year, month, day, 0, 0, 0);

    dataManager->setFestiveDate(numberOfFestive, festive);
    numberOfFestive += 1;
  }

  return true;
}