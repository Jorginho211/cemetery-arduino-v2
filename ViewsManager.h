#ifndef VIEWS_MANAGER_H
  #define VIEWS_MANAGER_H

  #include "View.h"
  #include "Peripherals.h"
  #include "DataManager.h"

  class ViewsManager: public View {
    public:
      void buttonPressed(NavigationAction pressed);
      void update(DateTime now);
      void draw();
      void setCurrentView(View *view);
      void mainTask(DateTime now);

      Peripherals *Peripherals;
    private:
      void checkChangeSummerWinterTime(DateTime now);
      void checkOpenCloseDoor(DateTime now);
      void performOpenCloseTask(bool isOpenProcess);
      void performLoudSpeakerTask(bool startingLoudSpeaker);

      View *m_CurrentView = nullptr;
      unsigned long m_LastPerformOpenCloseTaskMillis = 0;
      unsigned long m_LastPerformLoudSpeakerTaskMillis = 0;
  };
#endif