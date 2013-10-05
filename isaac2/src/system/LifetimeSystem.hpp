#ifndef				__LIFETIME_SYSTEM_HPP__
# define			__LIFETIME_SYSTEM_HPP__

#include			"System.hpp"
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


  virtual void			update(EntityData &entity, float time, const ALLEGRO_EVENT &)
  {
    Lifetime			*life = entity.getComponent<Lifetime>();

    life->time -= time;
    if (life->time <= 0.0f)
		entity.addComponent<Death>();
  }

private:
};

#endif				// __LIFETIME_SYSTEM_HPP__
