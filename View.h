#ifndef VIEW_H
  #define VIEW_H

  #include <RTClib.h>
  #include "NavigationReader.h"

  class View {
    public:
      virtual void buttonPressed(NavigationAction pressed);
      virtual void update(DateTime now);
      virtual void draw();
  };
#endif