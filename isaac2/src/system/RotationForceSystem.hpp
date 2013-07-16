#ifndef				__ROTATION_FORCE_SYSTEM_HPP__
# define			__ROTATION_FORCE_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

class				RotationForceSystem : public System
{
public:
  virtual ~RotationForceSystem()
  {}

  RotationForceSystem()
  {}

  void				init()
  {
    require<Rotation>();
    require<RotationForce>();
  }


  virtual void			update(unsigned int entity, float time, const ALLEGRO_EVENT &)
  {
    Rotation			*rot = ComponentManager::getInstance().getComponent<Rotation>(entity);
    RotationForce		*force = ComponentManager::getInstance().getComponent<RotationForce>(entity);

    Vector3d inc = force->force;
    inc *= time;
    rot->rotation += inc;
  }
private:
};

#endif				// __ROTATION_FORCE_SYSTEM_HPP__
