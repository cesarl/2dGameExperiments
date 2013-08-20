#ifndef				__SCALE_COMPONENT_HPP__
# define			__SCALE_COMPONENT_HPP__

#include			<glm/glm.hpp>
#include			"Component.hpp"

struct				Scale : public Component<Scale>
{
  glm::vec3			scale;

  Scale() : scale(glm::vec3(1.0f, 1.0f, 1.0f))
  {}
};

#endif				// __SCALE_COMPONENT_HPP__
