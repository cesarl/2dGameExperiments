#ifndef				__ROTATION_COMPONENT_HPP__
# define			__ROTATION_COMPONENT_HPP__

#include			"Component.hpp"

struct				Rotation : public Component<Rotation>
{
  Vector3d			rotation;
  Vector3d			axe;

  Rotation()
  {
    axe = Vector3d(0.5f, 0.5f, 0.5f);
  }
};

#endif				// __ROTATION_COMPONENT_HPP__
