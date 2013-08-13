#ifndef					__SCENE_MENU_HH__
# define				__SCENE_MENU_HH__

#include				<iostream> // for debug - to clear
#include				<string>
#include				"AScene.hh"
#include				"Entity.hh"
#include				"Image.hh"
#include				"GuiSelectableGroup.hh"
#include				"GuiSelectableText.hh"

class					SceneMenu : public AScene
{
public:
  SceneMenu();
  ~SceneMenu();
  virtual void				update(ALLEGRO_EVENT *event);
  virtual void				draw(ALLEGRO_EVENT *event);
  virtual void				input(ALLEGRO_EVENT *event);
  virtual void				receiveMessage(e_message type, bool activate);
  virtual bool				initialize();
  virtual void				uninitialize();
private: //variables
  Entity				title_;
  Entity				background_;
  GuiSelectableGroup			gui_;
};

namespace				MenuGui
{
  extern Entity				*particules_;
  void					selectMenuItem(GuiComponent *c);
  void					unselectMenuItem(GuiComponent *c);
  void					pressExitMenuItem(GuiComponent *c);
  void					pressNewGameMenuItem(GuiComponent *c);
  void					pressScoreMenuItem(GuiComponent *c);
}

#endif					// __SCENE_MENU_HH__
