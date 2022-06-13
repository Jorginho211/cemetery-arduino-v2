#ifndef VIEW_CONFIG_OPEN_CLOSE_DOOR_H
  #define VIEW_CONFIG_OPEN_CLOSE_DOOR_H

  #include "View.h"
  #include "ViewsManager.h"
  #include "Peripherals.h"
  #include "DataManager.h"
  #include "Utils.h"

  enum ConfigOpenCloseDoorOption {
    CONFIG_OPEN_CLOSE_DOOR_OPTION_OPEN_DATE_HOUR = 0,
    CONFIG_OPEN_CLOSE_DOOR_OPTION_OPEN_DATE_MINUTE = 1,
    CONFIG_OPEN_CLOSE_DOOR_OPTION_CLOSE_DATE_HOUR = 2,
    CONFIG_OPEN_CLOSE_DOOR_OPTION_CLOSE_DATE_MINUTE = 3,
    CONFIG_OPEN_CLOSE_DOOR_OPTION_DATE_COMPLETE = 4
  };

  class ViewConfigOpenCloseDoor: public View {
    public:
      ViewConfigOpenCloseDoor(ViewsManager *viewsManager);
      void buttonPressed(NavigationAction pressed);
      void update(DateTime now);
      void draw();
      
    private:
      ViewsManager *m_ViewsManager;
      ConfigOpenCloseDoorOption m_ConfigOpenCloseDoorOption;
      DateTime m_DateOpen;
      DateTime m_DateClose;
  };
#endif