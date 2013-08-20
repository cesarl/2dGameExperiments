#ifndef				__POSITION_COMPONENT_HPP__
# define			__POSITION_COMPONENT_HPP__

#include			<glm/glm.hpp>
#include			"Component.hpp"

struct				Position : public Component<Position>
{
  glm::vec3			position;
};

#endif				// __POSITION_COMPONENT_HPP__
