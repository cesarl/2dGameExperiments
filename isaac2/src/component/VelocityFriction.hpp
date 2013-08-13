#ifndef				__VELOCITY_FRICTION_COMPONENT_HPP__
# define			__VELOCITY_FRICTION_COMPONENT_HPP__

#include			"Component.hpp"

struct				VelocityFriction : public Component<VelocityFriction>
{
  float				friction;
};

#endif				// __VELOCITY_FRICTION_COMPONENT_HPP__
