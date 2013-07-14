#include			"SystemManager.hpp"
#include			"EntityManager.hpp"

void				SystemManager::update(float time, const ALLEGRO_EVENT &ev)
{
  EntityManager			&em = EntityManager::getInstance();
  std::map<int, System*>::iterator i;
  i = list_.begin();
  static float lastTime = al_get_time();

  while (i != list_.end())
    {
      i->second->updateBegin();
      EntityManager::iterator	&it = em.begin();
      while (it != em.end())
	{
	  if (i->second->match(*it))
	    i->second->update((*it).id, time - lastTime, ev);
	  ++it;
	}
      i->second->updateEnd();
      ++i;
    }
  lastTime = time;
  (void)time;
  (void)(ev);
}
