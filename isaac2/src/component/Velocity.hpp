#ifndef				__VELOCITY_COMPONENT_HPP__
# define			__VELOCITY_COMPONENT_HPP__

#include			"Component.hpp"

struct				Velocity : public Component<Velocity>
{
  Vector3d			velocity;
};

#endif				// __VELOCITY_COMPONENT_HPP__
