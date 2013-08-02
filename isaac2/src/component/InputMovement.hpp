#ifndef				__IPT_MOVEMENT_COMPONENT_HPP__
# define			__IPT_MOVEMENT_COMPONENT_HPP__

#include			"Component.hpp"

struct				InputMovement : public Component<InputMovement>
{
  float				speed;
  InputMovement()
  {
    speed = 0.0f;
  }
};

#endif				// __IPT_MOVEMENT_COMPONENT_HPP__
