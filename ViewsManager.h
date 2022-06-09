#ifndef VIEWS_MANAGER_H
  #define VIEWS_MANAGER_H

  #include "View.h"
  #include "Peripherals.h"

  class ViewsManager: public View {
    public:
      void buttonPressed(NavigationAction pressed);
      void update(DateTime now);
      void draw();
      void setCurrentView(View *view);

      Peripherals *Peripherals;
    private:
      View *m_CurrentView = nullptr;
  };
#endif