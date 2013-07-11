#include			"SystemManager.hpp"

void				SystemManager::update(const EntityData &entity , float time, const ALLEGRO_EVENT & ev)
{
  std::map<int, System*>::iterator it;
    
  it = list_.begin();
  while (it != list_.end())
    {
      if (it->second->match(entity))
	it->second->update(entity.id, time, ev);
      ++it;
    }
}

