#include "ViewConfigDate.h"

// Vistas requeridas
#include "ViewMain.h"

ViewConfigDate::ViewConfigDate(ViewsManager *viewsManager) {
  this->m_ViewsManager = viewsManager;

  this->m_ConfigDateOption = CONFIG_DATE_OPTION_DATE_DAY;
  this->m_Date = this->m_ViewsManager->Peripherals->Rtc.now();

  this->m_ViewsManager->Peripherals->Lcd->clear();
}

void ViewConfigDate::buttonPressed(NavigationAction pressed) {
  switch(pressed) {
    case NAVIGATION_UP:
      switch(this->m_ConfigDateOption) {
        case CONFIG_DATE_OPTION_DATE_DAY:
          this->m_Date = Utils::modifyDateTime(this->m_Date, DATETIME_INCREASE, DATETIME_SECTION_DAY);
          break;
        case CONFIG_DATE_OPTION_DATE_MONTH:
          this->m_Date = Utils::modifyDateTime(this->m_Date, DATETIME_INCREASE, DATETIME_SECTION_MONTH);
          break;
        case CONFIG_DATE_OPTION_DATE_YEAR:
          this->m_Date = Utils::modifyDateTime(this->m_Date, DATETIME_INCREASE, DATETIME_SECTION_YEAR);
          break;
        case CONFIG_DATE_OPTION_DATE_HOUR:
          this->m_Date = Utils::modifyDateTime(this->m_Date, DATETIME_INCREASE, DATETIME_SECTION_HOUR);
          break;
        case CONFIG_DATE_OPTION_DATE_MINUTE:
          this->m_Date = Utils::modifyDateTime(this->m_Date, DATETIME_INCREASE, DATETIME_SECTION_MINUTE);
          break;
      }
      break;
    case NAVIGATION_DOWN:
      switch(this->m_ConfigDateOption) {
        case CONFIG_DATE_OPTION_DATE_DAY:
          this->m_Date = Utils::modifyDateTime(this->m_Date, DATETIME_DECREASE, DATETIME_SECTION_DAY);
          break;
        case CONFIG_DATE_OPTION_DATE_MONTH:
          this->m_Date = Utils::modifyDateTime(this->m_Date, DATETIME_DECREASE, DATETIME_SECTION_MONTH);
          break;
        case CONFIG_DATE_OPTION_DATE_YEAR:
          this->m_Date = Utils::modifyDateTime(this->m_Date, DATETIME_DECREASE, DATETIME_SECTION_YEAR);
          break;
        case CONFIG_DATE_OPTION_DATE_HOUR:
          this->m_Date = Utils::modifyDateTime(this->m_Date, DATETIME_DECREASE, DATETIME_SECTION_HOUR);
          break;
        case CONFIG_DATE_OPTION_DATE_MINUTE:
          this->m_Date = Utils::modifyDateTime(this->m_Date, DATETIME_DECREASE, DATETIME_SECTION_MINUTE);
          break;
      }
      break;
    case NAVIGATION_OK:
      this->m_ConfigDateOption = (ConfigDateOption) (this->m_ConfigDateOption + 1);
      if (this->m_ConfigDateOption == CONFIG_DATE_OPTION_DATE_COMPLETE) {
        this->m_ViewsManager->Peripherals->Rtc.adjust(this->m_Date);
        this->m_ViewsManager->setCurrentView(new ViewMain(this->m_ViewsManager));
      }
      break;
  }
}

void ViewConfigDate::update(DateTime now) { }

void ViewConfigDate::draw() {
  Peripherals *peripherals = this->m_ViewsManager->Peripherals;

  peripherals->Lcd->setCursor(0,0);

  String nowStr = Utils::format00Number(this->m_Date.day()) + "/" +  Utils::format00Number(this->m_Date.month()) + "/" + String(this->m_Date.year());
  nowStr += " - " + Utils::format00Number(this->m_Date.hour()) + ":" + Utils::format00Number(this->m_Date.minute());

  peripherals->Lcd->setCursor(0, 0);
  peripherals->Lcd->print("Conf Data:");
  peripherals->Lcd->setCursor(0, 1);
  peripherals->Lcd->print(nowStr);

  switch(this->m_ConfigDateOption){
    case CONFIG_DATE_OPTION_DATE_DAY:
      peripherals->Lcd->setCursor(0,1);
      break;
    case CONFIG_DATE_OPTION_DATE_MONTH:
      peripherals->Lcd->setCursor(3,1);
      break;
    case CONFIG_DATE_OPTION_DATE_YEAR:
      peripherals->Lcd->setCursor(6,1);
      break;
    case CONFIG_DATE_OPTION_DATE_HOUR:
      peripherals->Lcd->setCursor(13,1);
      break;
    case CONFIG_DATE_OPTION_DATE_MINUTE:
      peripherals->Lcd->setCursor(16,1);
      break;
  }
  peripherals->Lcd->cursor();
}