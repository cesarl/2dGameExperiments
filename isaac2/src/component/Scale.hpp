#ifndef				__SCALE_COMPONENT_HPP__
# define			__SCALE_COMPONENT_HPP__

struct				Scale
{
  Vector3d			scale;

  Scale() : scale(Vector3d(1.0f, 1.0f, 1.0f))
  {}
};

#endif				// __SCALE_COMPONENT_HPP__