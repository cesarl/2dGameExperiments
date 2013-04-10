#ifndef					__SCENE_MENU_HH__
# define				__SCENE_MENU_HH__

#include				<iostream> // for debug - to clear
#include				<string>
#include				"AScene.hh"
#include				"Entity.hh"
#include				"Image.hh"
#include				"Text.hh"

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
  virtual void				receiveMessage(e_message type, void *data);
private: //member functions
  void					p_rollMenu(int direction);
private: //variables
  Entity				background_;
  Entity				title_;
  int					selectedChoice_;
  Entity				choices_[MAX_CHOICE];
  Entity				particules_;
};

#endif					// __SCENE_MENU_HH__
