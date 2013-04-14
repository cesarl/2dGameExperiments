#ifndef					__SCENE_MENU_HH__
# define				__SCENE_MENU_HH__

#include				<iostream> // for debug - to clear
#include				<string>
#include				"AScene.hh"
#include				"Entity.hh"
#include				"Room.hh"
#include				"PnjMap.tcc"
#include				"Room.tcc"
#include				"Decor.hh"

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
private: //variables
  Room<Decor>				room_;
  PnjMap<Entity>			pnjmap_;
  Entity				heros_;
};

#endif					// __SCENE_MENU_HH__
