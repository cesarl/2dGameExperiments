#ifndef					__EVENT_MANAGER_HH__
# define				__EVENT_MANAGER_HH__

#include                                <allegro5/allegro.h>
#include				<iostream>
#include				"SceneManager.hh"

class					SceneManager;

class					EventManager
{
public:
  EventManager();
  ~EventManager();
  void					play();
  void					pause();
  void					setSceneManager(SceneManager * sceneManager);
private:
  ALLEGRO_EVENT_QUEUE			*event_queue_;
  ALLEGRO_TIMER				*timer_;
  SceneManager				*sceneManager_;
  bool					pause_;
};

#endif					// __EVENT_MANAGER_HH__

