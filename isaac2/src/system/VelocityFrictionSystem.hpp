#ifndef				__VELOCITY_FRICTION_SYSTEM_HPP__
# define			__VELOCITY_FRICTION_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

class				VelocityFrictionSystem : public System
{
public:
  virtual ~VelocityFrictionSystem(){};
  VelocityFrictionSystem()
  {}
  void				init()
  {
    require<Velocity>();
    require<VelocityFriction>();
  }


  virtual void			update(unsigned int entity, float time, const ALLEGRO_EVENT &)
  {
    VelocityFriction		*fri = ComponentManager::getInstance().getComponent<VelocityFriction>(entity);
    Velocity			*vel = ComponentManager::getInstance().getComponent<Velocity>(entity);

    float t = fri->friction;

    t -= time;
    vel->velocity *= t;
  }

private:
};

#endif				// __VELOCITY_FRICTION_SYSTEM_HPP__
