#include			"SystemManager.hpp"


void				ImageSystem::update(unsigned int entity, float, const ALLEGRO_EVENT &)
{
  Position			*pos = ComponentManager::getInstance().getComponent<Position>(entity);
  Img				*img = ComponentManager::getInstance().getComponent<Img>(entity);

  img->img->draw3d(pos->position);
}

void				VelocitySystem::update(unsigned int entity, float, const ALLEGRO_EVENT &)
{
  Position			*pos = ComponentManager::getInstance().getComponent<Position>(entity);
  Velocity			*vel = ComponentManager::getInstance().getComponent<Velocity>(entity);

  pos->position += vel->velocity;;
}


void				SystemManager::add(System *sys)
{
list_.push_back(sys);
}

void				SystemManager::update(const EntityData &entity , float time, const ALLEGRO_EVENT & ev)
{
  std::vector<System*>::iterator it;
    
  it = list_.begin();
  while (it != list_.end())
    {
      if ((*it)->match(entity))
	(*it)->update(entity.id, time, ev);
      ++it;
    }
}
