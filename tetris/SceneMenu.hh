#ifndef					__SCENE_MENU_HH__
# define				__SCENE_MENU_HH__

#include				<iostream> // for debug - to clear
#include				"AScene.hh"
#include				"Entity.hh"
#include				"ContentComponentImage.hh"
#include				"ContentComponentText.hh"

#define					MAX_CHOICE 3

class					SceneMenu : public AScene
{
public:
  SceneMenu();
  ~SceneMenu();
  virtual void				update(ALLEGRO_EVENT *event);
  virtual void				draw(ALLEGRO_EVENT *event);
  virtual void				input(ALLEGRO_EVENT *event);
  virtual void				receiveMessage(e_message type, bool activate);
private: //member functions
  void					p_rollMenu(int direction);
private: //variables
  Entity				background_;
  Entity				title_;
  int					selectedChoice_;
  Entity				choices_[MAX_CHOICE];
};

#endif					// __SCENE_MENU_HH__