#include			"SystemManager.hpp"
#include			"EntityManager.hpp"

void				SystemManager::update(float time, const ALLEGRO_EVENT &ev)
{
  std::multimap<int, System*>::iterator i;
  static float lastTime = al_get_time();
  std::vector<EntityData>&list = EntityManager::getInstance().getList();
  float difTime = time - lastTime;

  i = list_.begin();
  
  while (i != list_.end())
  {
	  i->second->updateBegin(time, ev);

	  for (auto &e  : list)
	  {
		  // // if (!e.active)
		  // //   continue;
		  if (i->second->match(e))
			  i->second->update(e, difTime, ev);
	  }
	  i->second->updateEnd(time, ev);
	  ++i;
  }
  lastTime = time;
  (void)time;
  (void)(ev);
}

void				SystemManager::draw(float time, const ALLEGRO_EVENT &ev)
{
  static EntityManager		&em = EntityManager::getInstance();
  std::multimap<int, System*>::iterator i;
  static float lastTime = al_get_time();
  std::vector<EntityData>	&list = em.getList();

  i = drawList_.begin();  
  while (i != drawList_.end())
    {
      i->second->updateBegin(time, ev);
      ++i;
    }

  if (em.end() % 50 == 0)
    std::cout << "Entities : " << em.end() << std::endl;

  for (unsigned int	it = 0, mit = em.end(); it < mit; ++it)
    {
      EntityData		&e = list[it];

      i = drawList_.begin();  
      while (i != drawList_.end())
	  {
		  if (i->second->match(e))
		  {
			  i->second->update(e, time - lastTime, ev);
		  }
		  ++i;
	  }
  }

  i = drawList_.begin();  
  while (i != drawList_.end())
  {
	  i->second->updateEnd(time, ev);
	  ++i;
  }

  lastTime = time;
}
