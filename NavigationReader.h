#ifndef NAVIGATION_READER_H
  #define NAVIGATION_READER_H

  enum NavigationAction {
    NAVIGATION_NOTHING = 0,
    NAVIGATION_UP = 1,
    NAVIGATION_DOWN = 2,
    NAVIGATION_OK = 3
  };

  class NavigationReader {
    public:
      virtual void init();
      virtual NavigationAction read();
  };
#endif