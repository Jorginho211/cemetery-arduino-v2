#include "ViewMain.h"

// Vistas requeridas
#include "ViewMenu.h"

ViewMain::ViewMain(ViewsManager *viewsManager) {
  this->m_ViewsManager = viewsManager;
  this->m_Show2Points = true;

  this->m_ViewsManager->Peripherals->Lcd->clear();
}

void ViewMain::buttonPressed(NavigationAction pressed) { 
  if (pressed == NAVIGATION_OK) {
    this->m_ViewsManager->setCurrentView(new ViewMenu(this->m_ViewsManager, this), false);
  }
}

void ViewMain::update(DateTime now) {
  unsigned long currentUpdateMillis = millis();

  if(currentUpdateMillis - m_LastUpdateBlinkMillis >= 500){
    m_LastUpdateBlinkMillis = currentUpdateMillis;
    this->m_Show2Points = !this->m_Show2Points;
  }

  String blink = " ";
  if (this->m_Show2Points)
    blink = ":";
  
  this->m_StrDatetime = Utils::format00Number(now.day()) + "/" + Utils::format00Number(now.month()) + "/" + String(now.year());
  this->m_StrDatetime += " - " + Utils::format00Number(now.hour()) + blink + Utils::format00Number(now.minute());
}

void ViewMain::draw() {
  Peripherals *peripherals = this->m_ViewsManager->Peripherals;

  peripherals->Lcd->setCursor(0,0);
  peripherals->Lcd->print("Data e hora:");
  peripherals->Lcd->setCursor(0,1);
  peripherals->Lcd->print(this->m_StrDatetime);
  
  peripherals->Lcd->setCursor(0, 3);

  String systemStateStr = "Desactivado";
  if(peripherals->getSystemState())
    systemStateStr = "Activado   ";

  peripherals->Lcd->print("Estado: " + systemStateStr);
}