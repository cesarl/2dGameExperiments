#include			"SystemManager.hpp"
#include			"EntityManager.hpp"

void				SystemManager::update(float time, const ALLEGRO_EVENT &ev)
{
  static EntityManager		&em = EntityManager::getInstance();
  std::map<int, System*>::iterator i;
  static float lastTime = al_get_time();
  std::vector<EntityData>	&list = em.getList();

  i = list_.begin();
  
  while (i != list_.end())
    {
      i->second->updateBegin(time, ev);

      // #pragma omp sections
      // {
      for (unsigned int	it = 0, mit = em.end(); it < mit; ++it)
	{
	  EntityData		e = list[it];
	  // // if (!e.active)
	  // //   continue;
	  if (i->second->match(e))
	    i->second->update(it, time - lastTime, ev);
	}
    // }
      i->second->updateEnd(time, ev);
      ++i;
    }
  lastTime = time;
  (void)time;
  (void)(ev);
}
