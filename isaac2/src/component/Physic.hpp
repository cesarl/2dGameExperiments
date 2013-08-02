#ifndef				__PHYSIC_COMPONENT_HPP__
# define			__PHYSIC_COMPONENT_HPP__

#include			"Component.hpp"

struct				Physic : public Component<Physic>
{
  float				mass;
  bool				fixed;

  Physic()
  {
    mass = 1.0f;
    fixed = true;
  }
};

#endif				// __PHYSIC_COMPONENT_HPP__
