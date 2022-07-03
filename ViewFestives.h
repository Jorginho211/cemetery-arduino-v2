#ifndef VIEW_FESTIVES_H
  #define VIEW_FESTIVES_H

  #include "View.h"
  #include "ViewsManager.h"
  #include "Peripherals.h"
  #include "DataManager.h"
  #include "Utils.h"

  enum FestivesSyncSteps {
    FESTIVES_SYNC_NOTHING = 0,
    FESTIVES_SYNC_NEXT_STEP_SYNC = 1,
    FESTIVES_SYNC_SYNCING = 2,
    FESTIVES_SYNC_SUCCESS = 3,
    FESTIVES_SYNC_ERROR = 4
  };

  class ViewFestives: public View {
    public:
      ViewFestives(ViewsManager *viewsManager);
      void buttonPressed(NavigationAction pressed);
      void update(DateTime now);
      void draw();
      
    private:
      static const uint8_t MAX_OPTIONS_PER_VIEW = 3;

      ViewsManager *m_ViewsManager;
      uint8_t m_SelectedOption;
      uint8_t m_MaxOptions;
      FestivesSyncSteps m_SyncStep;
  };
#endif