#ifndef					__SCENE_MENU_HH__
# define				__SCENE_MENU_HH__

#include				<iostream> // for debug - to clear
#include				"AScene.hh"

class					SceneMenu : public AScene
{
public:
  SceneMenu();
  ~SceneMenu();
  virtual void				update(ALLEGRO_EVENT *event);
  virtual void				draw(ALLEGRO_EVENT *event);
  virtual void				input(ALLEGRO_EVENT *event);
};

#endif					// __SCENE_MENU_HH__
