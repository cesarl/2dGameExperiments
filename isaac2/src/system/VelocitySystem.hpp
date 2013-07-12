#ifndef				__VELOCITY_SYSTEM_HPP__
# define			__VELOCITY_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

class				VelocitySystem : public System
{
public:
  virtual ~VelocitySystem(){};
  VelocitySystem()
  {}
  void				init()
  {
    require<Position>();
    require<Velocity>();
  }


  virtual void			update(unsigned int entity, float, const ALLEGRO_EVENT &)
  {
    Position			*pos = ComponentManager::getInstance().getComponent<Position>(entity);
    Velocity			*vel = ComponentManager::getInstance().getComponent<Velocity>(entity);

    pos->position += vel->velocity;
  }

  virtual void			updateBegin(){};
  virtual void			updateEnd(){};

private:
};

#endif				// __VELOCITY_SYSTEM_HPP__
