#include "ViewFestives.h"

// Vistas requeridas
#include "ViewMain.h"

ViewFestives::ViewFestives(ViewsManager *viewsManager) {
  this->m_ViewsManager = viewsManager;

  DataManager *dataManager = DataManager::getInstance();
  this->m_SelectedOption = 0;
  this->m_MaxOptions = dataManager->getNumberOfFestives() + 2;
  
  this->m_SyncStep = FESTIVES_SYNC_NOTHING;

  this->m_ViewsManager->Peripherals->Lcd->clear();
  this->m_ViewsManager->Peripherals->Lcd->noCursor();
}

void ViewFestives::buttonPressed(NavigationAction pressed) {
  // Se esta sincronizando bloqueamos os botons
  if(this->m_SyncStep == FESTIVES_SYNC_SYNCING)
    return;
  
  // Si pulsamos calquera boton finalizado o proceso de sincronizado volvese a vista principal
  if(pressed != NAVIGATION_NOTHING && (this->m_SyncStep == FESTIVES_SYNC_SUCCESS || this->m_SyncStep == FESTIVES_SYNC_ERROR)) {
    this->m_ViewsManager->setCurrentView(new ViewMain(this->m_ViewsManager));
    return;
  }

  switch(pressed) {
    case NAVIGATION_UP:
        if(this->m_SelectedOption > 0)
          this->m_SelectedOption -= 1;
        else
          this-> m_SelectedOption = this->m_MaxOptions - 1;
      return;
    case NAVIGATION_DOWN:
      if(this->m_SelectedOption < this->m_MaxOptions - 1)
        this->m_SelectedOption += 1;
      else
        this->m_SelectedOption = 0;
      return;
    case NAVIGATION_NOTHING:
      return;
  }

  if (this->m_SelectedOption < this->m_MaxOptions - 2)
    return;

  View *nextView = NULL;
  if (this->m_SelectedOption == this->m_MaxOptions - 2) { // Pulsouse en Sincronizar
    this->m_SyncStep = FESTIVES_SYNC_NEXT_STEP_SYNC;
    return;
  }
  else if(this->m_SelectedOption == this->m_MaxOptions - 1) { // Pulsouse Atras
    nextView = new ViewMain(this->m_ViewsManager);
  }

  this->m_ViewsManager->setCurrentView(nextView);
}

void ViewFestives::update(DateTime now) {
  if (this->m_SyncStep == FESTIVES_SYNC_SYNCING) {
    if(this->m_ViewsManager->syncFestives())
      this->m_SyncStep = FESTIVES_SYNC_SUCCESS;
    else
      this->m_SyncStep = FESTIVES_SYNC_ERROR;
  }
}

void ViewFestives::draw() {
  Peripherals *peripherals = this->m_ViewsManager->Peripherals;

  if(this->m_SyncStep == FESTIVES_SYNC_NEXT_STEP_SYNC)
    peripherals->Lcd->clear();  

  peripherals->Lcd->setCursor(0,0);
  peripherals->Lcd->print("Festivos:");

  if(this->m_SyncStep == FESTIVES_SYNC_NEXT_STEP_SYNC) {
    peripherals->Lcd->setCursor(0, 2);
    peripherals->Lcd->print("Sincronizando...");
    this->m_SyncStep = FESTIVES_SYNC_SYNCING;
    return;
  }
  else if(this->m_SyncStep == FESTIVES_SYNC_SUCCESS) {
    peripherals->Lcd->setCursor(0, 2);
    peripherals->Lcd->print("Sinc Finalizada ");
    return;
  }
  else if(this->m_SyncStep == FESTIVES_SYNC_ERROR) {
    peripherals->Lcd->setCursor(0, 2);
    peripherals->Lcd->print("Erro Sincronizando");
    return;
  }

  uint8_t start = 0;
  if (this->m_SelectedOption - ViewFestives::MAX_OPTIONS_PER_VIEW + 1 >= 0) {
    start = this->m_SelectedOption - ViewFestives::MAX_OPTIONS_PER_VIEW + 1;
  }

  DataManager *dataManager = DataManager::getInstance();
  for(uint8_t i = start; i < start + ViewFestives::MAX_OPTIONS_PER_VIEW && i < this->m_MaxOptions; i++){
    peripherals->Lcd->setCursor(0, i - start + 1);
    String startOptionSymbol = "  ";
    if(i == this->m_SelectedOption){
      startOptionSymbol = "> ";
    }

    if(i < this->m_MaxOptions - 2) {
      DateTime festive = dataManager->getFestiveDate(i);
      String festiveStr = Utils::format00Number(festive.day()) + "/" + Utils::format00Number(festive.month()) + "/" + Utils::format00Number(festive.year());
      peripherals->Lcd->print(startOptionSymbol + festiveStr + "   ");
    }
    else if(i < this->m_MaxOptions - 1) {
      peripherals->Lcd->print(startOptionSymbol + "Sincronizar");
    }
    else if(i < this->m_MaxOptions) {
      peripherals->Lcd->print(startOptionSymbol + "Atras      ");
    }    
  }
}