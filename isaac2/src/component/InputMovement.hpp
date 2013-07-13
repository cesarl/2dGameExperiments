#ifndef				__IPT_MOVEMENT_COMPONENT_HPP__
# define			__IPT_MOVEMENT_COMPONENT_HPP__

struct				InputMovement
{
  float				speed;
  bool				up;
  bool				down;
  bool				left;
  bool				right;

  InputMovement()
  {
    up = down = left = right = false;
    speed = 0.0f;
  }
};

#endif				// __IPT_MOVEMENT_COMPONENT_HPP__
