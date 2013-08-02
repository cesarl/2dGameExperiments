#ifndef				__ROTATION_FORCE_COMPONENT_HPP__
# define			__ROTATION_FORCE_COMPONENT_HPP__

#include			"Component.hpp"

struct				RotationForce : public Component<RotationForce>
{
  Vector3d			force;
};

#endif				// __ROTATION_FORCE_COMPONENT_HPP__
