#include "ViewMenu.h"

// Vistas requeridas
#include "ViewConfigDate.h"
#include "ViewConfigLoudSpeaker.h"

ViewMenu::ViewMenu(ViewsManager *viewsManager, ViewMain *viewMain) {
  this->m_ViewsManager = viewsManager;
  this->m_ViewMain = viewMain;

  this->m_MenuOption = MENU_CONF_DATE;

  this->m_ViewsManager->Peripherals->Lcd->clear();
  this->m_ViewsManager->Peripherals->Lcd->noCursor();
}

void ViewMenu::buttonPressed(NavigationAction pressed) {
  switch(pressed) {
    case NAVIGATION_UP:
      if (this->m_MenuOption == MENU_CONF_DATE)
        this->m_MenuOption = MENU_GO_BACK;
      else
        this->m_MenuOption = (MenuOption) (this->m_MenuOption - 1);
      return;
    case NAVIGATION_DOWN:
      if (this->m_MenuOption == MENU_GO_BACK)
        this->m_MenuOption = MENU_CONF_DATE;
      else
        this->m_MenuOption = (MenuOption) (this->m_MenuOption + 1);
      return;
    case NAVIGATION_NOTHING:
      return;
  }

  View *nextView = NULL;
  switch(this->m_MenuOption) {
    case MENU_CONF_DATE:
      nextView = new ViewConfigDate(this->m_ViewsManager);
      break;
    case MENU_CONF_LOUD_SPEAKER:
      nextView = new ViewConfigLoudSpeaker(this->m_ViewsManager);
      break;
    case MENU_CONF_DOOR:
      break;
    case MENU_CONF_DAYS_OF_WEEK:
      break;
    case MENU_GO_BACK:
      nextView = new ViewMain(this->m_ViewsManager);
      break;
  }

  delete this->m_ViewMain;
  this->m_ViewsManager->setCurrentView(nextView);
}

void ViewMenu::update(DateTime now) {
  m_ViewMain->update(now); // Se hacen las mismas operaciones que en la vista principal
}

void ViewMenu::draw() {
  Peripherals *peripherals = this->m_ViewsManager->Peripherals;

  peripherals->Lcd->setCursor(0,0);
  uint8_t start = 0;
  if (this->m_MenuOption - ViewMenu::MAX_OPTIONS_PER_VIEW + 1 >= 0) {
    start = this->m_MenuOption - ViewMenu::MAX_OPTIONS_PER_VIEW + 1;
  }

  for(uint8_t i = start; i < start + ViewMenu::MAX_OPTIONS_PER_VIEW && i < this->NUM_OPTIONS_MENU; i++){
    peripherals->Lcd->setCursor(0, i - start);
    String startOptionSymbol = "  ";
    if(i == this->m_MenuOption){
      startOptionSymbol = "> ";
    }

    peripherals->Lcd->print(startOptionSymbol + this->MENU_OPTIONS_TITLE[i]);
  }
}