#include			"SystemManager.hpp"
#include			"EntityManager.hpp"

void				SystemManager::update(float time, const ALLEGRO_EVENT &ev)
{
  static EntityManager		&em = EntityManager::getInstance();
  std::map<int, System*>::iterator i;
  static float lastTime = al_get_time();

  i = list_.begin();
  while (i != list_.end())
    {
      i->second->updateBegin(time, ev);
      EntityManager::iterator	&it = em.begin();
      while (it != em.end())
	{
	  if (i->second->match(*it))
	    i->second->update((*it).id, time - lastTime, ev);
	  ++it;
	}
      i->second->updateEnd(time, ev);
      ++i;
    }
  lastTime = time;
  (void)time;
  (void)(ev);
}
