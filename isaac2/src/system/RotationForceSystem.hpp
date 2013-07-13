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


  virtual void			update(unsigned int entity, float, const ALLEGRO_EVENT &)
  {
    Rotation			*rot = ComponentManager::getInstance().getComponent<Rotation>(entity);
    RotationForce		*force = ComponentManager::getInstance().getComponent<RotationForce>(entity);

    rot->rotation += force->force;
  }

  virtual void			updateBegin()
  {}

  virtual void			updateEnd()
  {}

private:
};

#endif				// __ROTATION_FORCE_SYSTEM_HPP__
