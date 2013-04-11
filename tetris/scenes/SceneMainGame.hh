#ifndef					__SCENE_MAIN_GAME_HH__
# define				__SCENE_MAIN_GAME_HH__

#include				<iostream> // for debug - to clear
#include				"AScene.hh"
#include				"Entity.hh"
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
  virtual void				receiveMessage(e_message type, void *data);
private: //variables
  Entity				background_;
  Entity				mainBackground_;
  TetrisGrid				grid_;
  int					score_;
};

#endif					// __SCENE_MAIN_GAME_HH__








