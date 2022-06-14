#ifndef VIEW_MAIN_H
  #define VIEW_MAIN_H

  #include "View.h"
  #include "ViewsManager.h"
  #include "Peripherals.h"
  #include "DataManager.h"
  #include "Utils.h"

  class ViewMain: public View {
    public:
      ViewMain(ViewsManager *viewsManager);
      void buttonPressed(NavigationAction pressed);
      void update(DateTime now);
      void draw();
      
    private:
      ViewsManager *m_ViewsManager;
      unsigned long m_LastUpdateBlinkMillis;
      bool m_Show2Points;
      String m_StrDatetime;
  };
#endif