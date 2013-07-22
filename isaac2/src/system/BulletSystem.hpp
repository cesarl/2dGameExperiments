#ifndef				__BULLET_SYSTEM_HPP__
# define			__BULLET_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

class				BulletSystem : public System
{
public:
  virtual ~BulletSystem()
  {}

  BulletSystem()
  {}

  void				init()
  {
    require<Lifetime>();
    require<Collision>();
  }

  virtual void			update(unsigned int entity, float, const ALLEGRO_EVENT &)
  {
    // Collision			*col = ComponentManager::getInstance().getComponent<Collision>(entity);
    Lifetime			*life = ComponentManager::getInstance().getComponent<Lifetime>(entity);

    life->time = 0.0f;
  }
private:
};

#endif				// __BULLET_SYSTEM_HPP__
