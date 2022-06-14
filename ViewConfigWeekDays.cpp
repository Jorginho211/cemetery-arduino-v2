#include "ViewConfigWeekDays.h"

// Vistas requeridas
#include "ViewMain.h"

ViewConfigWeekDays::ViewConfigWeekDays(ViewsManager *viewsManager) {
  this->m_ViewsManager = viewsManager;

  this->m_ConfigWeekDaysPos = 0;
  this->m_WeekDays = DataManager::getInstance()->getWeekDays();

  this->m_ViewsManager->Peripherals->Lcd->clear();
}

void ViewConfigWeekDays::buttonPressed(NavigationAction pressed) {
  switch(pressed) {
    case NAVIGATION_UP:
      if (this->m_ConfigWeekDaysPos > 0)
        this->m_ConfigWeekDaysPos--;
      break;
    case NAVIGATION_DOWN:
      if (this->m_ConfigWeekDaysPos < 7)
        this->m_ConfigWeekDaysPos++;
      break;
    case NAVIGATION_OK:
      if(this->m_ConfigWeekDaysPos == 7) {
        DataManager::getInstance()->setWeekDays(this->m_WeekDays);
        this->m_ViewsManager->setCurrentView(new ViewMain(this->m_ViewsManager));
        return;
      }

      this->m_WeekDays ^= (1 << this->m_ConfigWeekDaysPos);
      break;
  }
}

void ViewConfigWeekDays::update(DateTime now) { }

void ViewConfigWeekDays::draw() {
  Peripherals *peripherals = this->m_ViewsManager->Peripherals;

  peripherals->Lcd->setCursor(0,0);
  peripherals->Lcd->print(" D  L  M  X  J  V  S");
  peripherals->Lcd->setCursor(0,1);

  for(uint8_t dayOfWeek = 0; dayOfWeek < 7; dayOfWeek++){
    uint8_t pos = dayOfWeek * 3;
    peripherals->Lcd->setCursor(pos, 1);

    if(this->m_ConfigWeekDaysPos == dayOfWeek) {
      peripherals->Lcd->print(">");
    }
    else {
      peripherals->Lcd->print(" ");
    }

    bool isSelectedDayOfWeek = ((this->m_WeekDays >> dayOfWeek) & 0x01) == 0x01;
    if(isSelectedDayOfWeek) {
      peripherals->Lcd->print("*"); 
    }
    else {
      peripherals->Lcd->print(" ");
    }
  }

  String confirmOptionArrow = " ";
  if(this->m_ConfigWeekDaysPos == 7){
    confirmOptionArrow = ">";
  }
  peripherals->Lcd->setCursor(0,3);
  peripherals->Lcd->print(confirmOptionArrow + " Confirmar");
}