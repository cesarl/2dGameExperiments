#ifndef				__ROTATION_COMPONENT_HPP__
# define			__ROTATION_COMPONENT_HPP__

#include			<glm/glm.hpp>
#include			"Component.hpp"

struct				Rotation : public Component<Rotation>
{
  glm::vec3			rotation;
  glm::vec3			axe;

  Rotation()
  {
    axe = glm::vec3(0.5f, 0.5f, 0.5f);
  }
};

#endif				// __ROTATION_COMPONENT_HPP__
