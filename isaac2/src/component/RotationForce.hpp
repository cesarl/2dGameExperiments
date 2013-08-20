#ifndef				__ROTATION_FORCE_COMPONENT_HPP__
# define			__ROTATION_FORCE_COMPONENT_HPP__

#include			<glm/glm.hpp>
#include			"Component.hpp"

struct				RotationForce : public Component<RotationForce>
{
  glm::vec3			force;
};

#endif				// __ROTATION_FORCE_COMPONENT_HPP__
