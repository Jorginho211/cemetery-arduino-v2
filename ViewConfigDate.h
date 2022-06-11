#ifndef VIEW_CONFIG_DATE_H
  #define VIEW_CONFIG_DATE_H

  #include "View.h"
  #include "ViewsManager.h"
  #include "Peripherals.h"
  #include "Utils.h"

  enum ConfigDateOption {
    OPTION_DATE_DAY = 0,
    OPTION_DATE_MONTH = 1,
    OPTION_DATE_YEAR = 2,
    OPTION_DATE_HOUR = 3,
    OPTION_DATE_MINUTE = 4,
    OPTION_DATE_COMPLETE = 5
  };

  class ViewConfigDate: public View {
    public:
      ViewConfigDate(ViewsManager *viewsManager);
      void buttonPressed(NavigationAction pressed);
      void update(DateTime now);
      void draw();
      
    private:
      ViewsManager *m_ViewsManager;
      ConfigDateOption m_ConfigDateOption;
      DateTime m_Date;
  };
#endif