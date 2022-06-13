#ifndef VIEW_CONFIG_WEEK_DAYS_H
  #define VIEW_CONFIG_WEEK_DAYS_H

  #include "View.h"
  #include "ViewsManager.h"
  #include "Peripherals.h"
  #include "DataManager.h"

  class ViewConfigWeekDays: public View {
    public:
      ViewConfigWeekDays(ViewsManager *viewsManager);
      void buttonPressed(NavigationAction pressed);
      void update(DateTime now);
      void draw();
      
    private:
      ViewsManager *m_ViewsManager;
      uint8_t m_ConfigWeekDaysPos;
      uint8_t m_WeekDays;
  };
#endif