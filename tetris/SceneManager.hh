#ifndef					__SCENE_MANAGER_HH__
# define				__SCENE_MANAGER_HH__

#include                                <allegro5/allegro.h>
#include				<string>
#include				<list>
#include				<algorithm>
#include				"AScene.hh"
#include				"EventManager.hh"

class					AScene;
class					EventManager;

enum					E_PRIORITY
  {
    HIGH,
    MEDIUM,
    LOW
  };

class					SceneManager
{
public:
  SceneManager();
  ~SceneManager();
  void					add(AScene *scene, int priority = MEDIUM);
  AScene				*remove(AScene *scene);
  AScene				*get(std::string const & name);
  void					setVisibleAll(bool val);
  void					setActiveAll(bool val);
  void					setPriority(AScene *scene, int priority);
  void					setEventManager(EventManager * eventManager);
  void					updateEvent(ALLEGRO_EVENT *event);
  void					drawEvent(ALLEGRO_EVENT *event);
  void					inputEvent(ALLEGRO_EVENT *event);
  void					exit();
private:
  std::list<AScene*>			collection_;
  EventManager				*eventManager_;
  typedef std::list<AScene*>::iterator	t_iter;
};

#endif					// __SCENE_MANAGER_HH__
