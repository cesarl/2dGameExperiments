#ifndef					__SCENE_MAIN_GAME_HH__
# define				__SCENE_MAIN_GAME_HH__

#include				<iostream> // for debug - to clear
#include				"AScene.hh"
#include				"Entity.hh"
#include				"ContentComponentImage.hh"
#include				"ContentComponentText.hh"
#include				"TetrisGrid.hh"

class					SceneMainGame : public AScene
{
public:
  SceneMainGame();
  ~SceneMainGame();
  virtual void				update(ALLEGRO_EVENT *event);
  virtual void				draw(ALLEGRO_EVENT *event);
  virtual void				input(ALLEGRO_EVENT *event);
  virtual void				receiveMessage(e_message type, bool activate);
private: //variables
  Entity				background_;
  TetrisGrid				grid_;
};

#endif					// __SCENE_MAIN_GAME_HH__








