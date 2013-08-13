#ifndef				__POSITION_COMPONENT_HPP__
# define			__POSITION_COMPONENT_HPP__

#include			"Component.hpp"

struct				Position : public Component<Position>
{
  Vector3d			position;
};

#endif				// __POSITION_COMPONENT_HPP__
