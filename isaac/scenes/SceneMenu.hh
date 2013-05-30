#ifndef					__SCENE_MENU_HH__
# define				__SCENE_MENU_HH__

#include				<iostream> // for debug - to clear
#include				<string>
#include				"AScene.hh"
#include				"Entity.hh"
#include				"Room.hh"
#include				"PnjMap.hpp"
#include				"Room.hpp"
#include				"Decor.hh"
#include				"Pnj.hh"
#include				"Grid.hh"

class					SceneMenu : public AScene
{
public:
  SceneMenu();
  ~SceneMenu();
  virtual bool				initialize();
  virtual void				uninitialize();
  virtual void				update(ALLEGRO_EVENT *event);
  virtual void				draw(ALLEGRO_EVENT *event);
  virtual void				input(ALLEGRO_EVENT *event);
  virtual void				receiveMessage(e_message type, bool activate);
private: //variables
  Room<Decor>				room_;
  PnjMap<Pnj>				pnjmap_;
  Entity				heros_;
  Grid					grid_;
};

#endif					// __SCENE_MENU_HH__
