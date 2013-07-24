#ifndef				__LIFETIME_SYSTEM_HPP__
# define			__LIFETIME_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

class				LifetimeSystem : public System
{
public:
  virtual ~LifetimeSystem(){};
  LifetimeSystem()
  {}
  void				init()
  {
    require<Lifetime>();
  }


  virtual void			update(unsigned int entity, float time, const ALLEGRO_EVENT &)
  {
    Lifetime			*life = ComponentManager::getInstance().getComponent<Lifetime>(entity);

    life->time -= time;
    if (life->time <= 0.0f)
      ComponentManager::getInstance().addComponent<Death>(entity);
  }

private:
};

#endif				// __LIFETIME_SYSTEM_HPP__
