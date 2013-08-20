#ifndef				__VELOCITY_COMPONENT_HPP__
# define			__VELOCITY_COMPONENT_HPP__

#include			<glm/glm.hpp>
#include			"Component.hpp"

struct				Velocity : public Component<Velocity>
{
   glm::vec3			velocity;
};

#endif				// __VELOCITY_COMPONENT_HPP__
