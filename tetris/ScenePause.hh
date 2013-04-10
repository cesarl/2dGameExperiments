#ifndef					__SCENE_PAUSE_HH__
# define				__SCENE_PAUSE_HH__

#include				<iostream> // for debug - to clear
#include				"AScene.hh"
#include				"Entity.hh"

#define					MAX_CHOICE 3

class					ScenePause : public AScene
{
public:
  ScenePause();
  ~ScenePause();
  virtual void				update(ALLEGRO_EVENT *event);
  virtual void				draw(ALLEGRO_EVENT *event);
  virtual void				input(ALLEGRO_EVENT *event);
  virtual void				receiveMessage(e_message type, bool activate);
  virtual void				receiveMessage(e_message type, void *data);
private: //member functions
  void					p_rollPause(int direction);
private: //variables
  Entity				background_;
  Entity				title_;
  int					selectedChoice_;
  Entity				choices_[MAX_CHOICE];
};

#endif					// __SCENE_PAUSE_HH__
