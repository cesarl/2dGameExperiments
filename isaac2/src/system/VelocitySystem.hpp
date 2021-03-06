#ifndef				__VELOCITY_SYSTEM_HPP__
# define			__VELOCITY_SYSTEM_HPP__

#include			"System.hpp"
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


  virtual void			update(EntityData &entity, float time, const ALLEGRO_EVENT &)
  {
    Position			*pos = entity.getComponent<Position>();
    Velocity			*vel = entity.getComponent<Velocity>();

    glm::vec3 inc = vel->velocity;
    inc *= time;
    pos->position += inc;
  }

private:
};

#endif				// __VELOCITY_SYSTEM_HPP__
