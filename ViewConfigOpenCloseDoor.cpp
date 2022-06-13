#include "ViewConfigOpenCloseDoor.h"

// Vistas requeridas
#include "ViewMain.h"

ViewConfigOpenCloseDoor::ViewConfigOpenCloseDoor(ViewsManager *viewsManager) {
  this->m_ViewsManager = viewsManager;

  this->m_ConfigOpenCloseDoorOption = CONFIG_OPEN_CLOSE_DOOR_OPTION_OPEN_DATE_HOUR;
  this->m_DateOpen = DataManager::getInstance()->getOpenDoorTime();
  this->m_DateClose = DataManager::getInstance()->getCloseDoorTime();

  this->m_ViewsManager->Peripherals->Lcd->clear();
}

void ViewConfigOpenCloseDoor::buttonPressed(NavigationAction pressed) {
  switch(pressed) {
    case NAVIGATION_UP:
      switch(this->m_ConfigOpenCloseDoorOption) {
        case CONFIG_OPEN_CLOSE_DOOR_OPTION_OPEN_DATE_HOUR:
          this->m_DateOpen = Utils::modifyDateTime(this->m_DateOpen, DATETIME_INCREASE, DATETIME_SECTION_HOUR);
          break;
        case CONFIG_OPEN_CLOSE_DOOR_OPTION_OPEN_DATE_MINUTE:
          this->m_DateOpen = Utils::modifyDateTime(this->m_DateOpen, DATETIME_INCREASE, DATETIME_SECTION_MINUTE);
          break;
        case CONFIG_OPEN_CLOSE_DOOR_OPTION_CLOSE_DATE_HOUR:
          this->m_DateClose = Utils::modifyDateTime(this->m_DateClose, DATETIME_INCREASE, DATETIME_SECTION_HOUR);
          break;
        case CONFIG_OPEN_CLOSE_DOOR_OPTION_CLOSE_DATE_MINUTE:
          this->m_DateClose = Utils::modifyDateTime(this->m_DateClose, DATETIME_INCREASE, DATETIME_SECTION_MINUTE);
          break;
      }
      break;
    case NAVIGATION_DOWN:
      switch(this->m_ConfigOpenCloseDoorOption) {
        case CONFIG_OPEN_CLOSE_DOOR_OPTION_OPEN_DATE_HOUR:
          this->m_DateOpen = Utils::modifyDateTime(this->m_DateOpen, DATETIME_DECREASE, DATETIME_SECTION_HOUR);
          break;
        case CONFIG_OPEN_CLOSE_DOOR_OPTION_OPEN_DATE_MINUTE:
          this->m_DateOpen = Utils::modifyDateTime(this->m_DateOpen, DATETIME_DECREASE, DATETIME_SECTION_MINUTE);
          break;
        case CONFIG_OPEN_CLOSE_DOOR_OPTION_CLOSE_DATE_HOUR:
          this->m_DateClose = Utils::modifyDateTime(this->m_DateClose, DATETIME_DECREASE, DATETIME_SECTION_HOUR);
          break;
        case CONFIG_OPEN_CLOSE_DOOR_OPTION_CLOSE_DATE_MINUTE:
          this->m_DateClose = Utils::modifyDateTime(this->m_DateClose, DATETIME_DECREASE, DATETIME_SECTION_MINUTE);
          break;
      }
      break;
    case NAVIGATION_OK:
      this->m_ConfigOpenCloseDoorOption = (ConfigOpenCloseDoorOption) (this->m_ConfigOpenCloseDoorOption + 1);
      if (this->m_ConfigOpenCloseDoorOption == CONFIG_OPEN_CLOSE_DOOR_OPTION_DATE_COMPLETE) {
        DataManager::getInstance()->setOpenDoorTime(this->m_DateOpen);
        DataManager::getInstance()->setCloseDoorTime(this->m_DateClose);
        this->m_ViewsManager->setCurrentView(new ViewMain(this->m_ViewsManager));
      }
      break;
  }
}

void ViewConfigOpenCloseDoor::update(DateTime now) { }

void ViewConfigOpenCloseDoor::draw() {
  Peripherals *peripherals = this->m_ViewsManager->Peripherals;

  peripherals->Lcd->setCursor(0,0);

  String openTimeStr = "Hora Abrir: " + Utils::format00Number(this->m_DateOpen.hour()) + ":" +  Utils::format00Number(this->m_DateOpen.minute());
  String closeTimeStr = "Hora Peche: " + Utils::format00Number(this->m_DateClose.hour()) + ":" +  Utils::format00Number(this->m_DateClose.minute());

  peripherals->Lcd->setCursor(0, 0);
  peripherals->Lcd->print("Conf. Portal:");
  peripherals->Lcd->setCursor(2,1);
  peripherals->Lcd->print(openTimeStr);
  peripherals->Lcd->setCursor(2,2);
  peripherals->Lcd->print(closeTimeStr);

  switch(this->m_ConfigOpenCloseDoorOption){
    case CONFIG_OPEN_CLOSE_DOOR_OPTION_OPEN_DATE_HOUR:
      peripherals->Lcd->setCursor(14,1);
      break;
    case CONFIG_OPEN_CLOSE_DOOR_OPTION_OPEN_DATE_MINUTE:
      peripherals->Lcd->setCursor(17,1);
      break;
    case CONFIG_OPEN_CLOSE_DOOR_OPTION_CLOSE_DATE_HOUR:
      peripherals->Lcd->setCursor(14,2);
      break;
    case CONFIG_OPEN_CLOSE_DOOR_OPTION_CLOSE_DATE_MINUTE:
      peripherals->Lcd->setCursor(17,2);
      break;
  }
  peripherals->Lcd->cursor();
}