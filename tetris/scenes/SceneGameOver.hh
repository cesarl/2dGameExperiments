#ifndef					__SCENE_GAME_OVER_HH__
# define				__SCENE_GAME_OVER_HH__

#include				<iostream> // for debug - to clear
#include				"AScene.hh"
#include				"Entity.hh"
#include				"SaveManager.hh"

#define					MAX_CHOICE_GO 2

class					SceneGameOver : public AScene
{
public:
  SceneGameOver();
  ~SceneGameOver();
  virtual void				update(ALLEGRO_EVENT *event);
  virtual void				draw(ALLEGRO_EVENT *event);
  virtual void				input(ALLEGRO_EVENT *event);
  virtual void				receiveMessage(e_message type, bool activate);
  virtual bool				initialize();
  virtual void				uninitialize();
private: //member functions
  void					p_rollChoices(int direction);
  void					p_saveScore();
private: //variables
  Entity				score_;
  Entity				title_;
  Entity				playerNameLabel_;
  Entity				playerName_;
  int					selectedChoice_;
  Entity				choices_[MAX_CHOICE_GO];
};

#endif					// __SCENE_GAME_OVER_HH__
