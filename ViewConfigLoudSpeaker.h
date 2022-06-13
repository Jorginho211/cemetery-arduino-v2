#ifndef VIEW_CONFIG_LOUD_SPEAKER_H
  #define VIEW_CONFIG_LOUD_SPEAKER_H

  #include "View.h"
  #include "ViewsManager.h"
  #include "Peripherals.h"
  #include "DataManager.h"
  #include "Utils.h"

  enum ConfigLoudSpeakerOption {
    CONFIG_LOUD_SPEAKER_OPTION_DATE_HOUR = 0,
    CONFIG_LOUD_SPEAKER_OPTION_DATE_MINUTE = 1,
    CONFIG_LOUD_SPEAKER_OPTION_DATE_COMPLETE = 2
  };

  class ViewConfigLoudSpeaker: public View {
    public:
      ViewConfigLoudSpeaker(ViewsManager *viewsManager);
      void buttonPressed(NavigationAction pressed);
      void update(DateTime now);
      void draw();
      
    private:
      ViewsManager *m_ViewsManager;
      ConfigLoudSpeakerOption m_ConfigLoudSpeakerOption;
      DateTime m_Date;
  };
#endif