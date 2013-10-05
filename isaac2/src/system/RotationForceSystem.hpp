#ifndef				__ROTATION_FORCE_SYSTEM_HPP__
# define			__ROTATION_FORCE_SYSTEM_HPP__

#include			"System.hpp"
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


  virtual void			update(EntityData &entity, float time, const ALLEGRO_EVENT &)
  {
    Rotation			*rot = entity.getComponent<Rotation>();
    RotationForce		*force = entity.getComponent<RotationForce>();

    glm::vec3 inc = force->force;
    inc *= time;
    rot->rotation += inc;
  }
private:
};

#endif				// __ROTATION_FORCE_SYSTEM_HPP__
