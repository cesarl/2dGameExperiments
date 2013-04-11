#ifndef					__EVENT_MANAGER_HH__
# define				__EVENT_MANAGER_HH__

#include                                <allegro5/allegro.h>
#include				<iostream>
#include				<list>
#include				<algorithm>
#include				"SceneManager.hh"
#include				"Input.hh"

class					SceneManager;
class					Input;

class					EventManager
{
public:
  ~EventManager();
  static EventManager			*getInstance();
  void					play();
  void					pause();
  void					setSceneManager(SceneManager * sceneManager);
  void					inputSubscribe(Input *input);
  void					inputUnsubscribe(Input *input);
private:
  ALLEGRO_EVENT_QUEUE			*event_queue_;
  ALLEGRO_TIMER				*timer_;
  SceneManager				*sceneManager_;
  bool					pause_;
  std::list<Input*>			inputSubscribeList_;
  EventManager();
  typedef std::list<Input*>::iterator	t_iter;
};

#endif					// __EVENT_MANAGER_HH__

