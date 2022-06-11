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

void ViewsManager::setCurrentView(View *view, bool deleteView = true) {
  if (deleteView && this->m_CurrentView != nullptr)
    delete this->m_CurrentView;
    
  this->m_CurrentView = view;
}