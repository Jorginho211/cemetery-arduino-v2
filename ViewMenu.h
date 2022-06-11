#ifndef VIEW_MENU_H
  #define VIEW_MENU_H

  #include "View.h"
  #include "ViewsManager.h"
  #include "Peripherals.h"

  // Vistas requeridas
  #include "ViewMain.h"

  enum MenuOption {
    MENU_CONF_DATE = 0,
    MENU_CONF_LOUD_SPEAKER = 1,
    MENU_CONF_DOOR = 2,
    MENU_CONF_DAYS_OF_WEEK = 3,
    MENU_GO_BACK = 4
  };

  class ViewMenu: public View {
    public:
      ViewMenu(ViewsManager *viewsManager, ViewMain *viewMain);
      void buttonPressed(NavigationAction pressed);
      void update(DateTime now);
      void draw();
      
    private:
      static const uint8_t NUM_OPTIONS_MENU = 5;
      static const uint8_t MAX_OPTIONS_PER_VIEW = 4;

      ViewMain *m_ViewMain;
      ViewsManager *m_ViewsManager;
      MenuOption m_MenuOption;
      const String MENU_OPTIONS_TITLE[ViewMenu::NUM_OPTIONS_MENU] = { // Levan espacios para completar e limpar o listado
        "Conf Data         ",
        "Conf Megafonia    ",
        "Conf Portal       ",
        "Conf Dias Semana  ",
        "Atras             "
      };
  };
#endif