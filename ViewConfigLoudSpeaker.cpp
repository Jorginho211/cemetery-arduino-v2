#include "ViewConfigLoudSpeaker.h"

// Vistas requeridas
#include "ViewMain.h"

ViewConfigLoudSpeaker::ViewConfigLoudSpeaker(ViewsManager *viewsManager) {
  this->m_ViewsManager = viewsManager;

  this->m_ConfigLoudSpeakerOption = CONFIG_LOUD_SPEAKER_OPTION_DATE_HOUR;
  this->m_Date = DataManager::getInstance()->getLoudSpeakerTime();

  this->m_ViewsManager->Peripherals->Lcd->clear();
}

void ViewConfigLoudSpeaker::buttonPressed(NavigationAction pressed) {
  switch(pressed) {
    case NAVIGATION_UP:
      switch(this->m_ConfigLoudSpeakerOption) {
        case CONFIG_LOUD_SPEAKER_OPTION_DATE_HOUR:
          this->m_Date = Utils::modifyDateTime(this->m_Date, DATETIME_INCREASE, DATETIME_SECTION_HOUR);
          break;
        case CONFIG_LOUD_SPEAKER_OPTION_DATE_MINUTE:
          this->m_Date = Utils::modifyDateTime(this->m_Date, DATETIME_INCREASE, DATETIME_SECTION_MINUTE);
          break;
      }
      break;
    case NAVIGATION_DOWN:
      switch(this->m_ConfigLoudSpeakerOption) {
        case CONFIG_LOUD_SPEAKER_OPTION_DATE_HOUR:
          this->m_Date = Utils::modifyDateTime(this->m_Date, DATETIME_DECREASE, DATETIME_SECTION_HOUR);
          break;
        case CONFIG_LOUD_SPEAKER_OPTION_DATE_MINUTE:
          this->m_Date = Utils::modifyDateTime(this->m_Date, DATETIME_DECREASE, DATETIME_SECTION_MINUTE);
          break;
      }
      break;
    case NAVIGATION_OK:
      this->m_ConfigLoudSpeakerOption = (ConfigLoudSpeakerOption) (this->m_ConfigLoudSpeakerOption + 1);
      if (this->m_ConfigLoudSpeakerOption == CONFIG_LOUD_SPEAKER_OPTION_DATE_COMPLETE) {
        DataManager::getInstance()->setLoudSpeakerTime(this->m_Date);
        this->m_ViewsManager->setCurrentView(new ViewMain(this->m_ViewsManager));
      }
      break;
  }
}

void ViewConfigLoudSpeaker::update(DateTime now) { }

void ViewConfigLoudSpeaker::draw() {
  Peripherals *peripherals = this->m_ViewsManager->Peripherals;

  peripherals->Lcd->setCursor(0,0);

  String loudSpeakerTimeStr = "Hora: " + Utils::format00Number(this->m_Date.hour()) + ":" +  Utils::format00Number(this->m_Date.minute());

  peripherals->Lcd->setCursor(0, 0);
  peripherals->Lcd->print("Conf. Megafonia:");
  peripherals->Lcd->setCursor(2,1);
  peripherals->Lcd->print(loudSpeakerTimeStr);

  switch(this->m_ConfigLoudSpeakerOption){
    case CONFIG_LOUD_SPEAKER_OPTION_DATE_HOUR:
      peripherals->Lcd->setCursor(8,1);
      break;
    case CONFIG_LOUD_SPEAKER_OPTION_DATE_MINUTE:
      peripherals->Lcd->setCursor(11,1);
      break;
  }
  peripherals->Lcd->cursor();
}