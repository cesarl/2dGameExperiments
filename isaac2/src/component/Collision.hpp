#ifndef				__COLLISION_COMPONENT_HPP__
# define			__COLLISION_COMPONENT_HPP__

#include			<list>
#include			"Component.hpp"

struct				Collision : public Component<Collision>
{
  std::list<unsigned int>	list;
  Collision			operator=(const Collision &)
  {
    // list(std::list<unsigned int>(o.list.begin(), o.list.end()))
    return *this;
  }
  Collision(const Collision &o) :
    list(std::list<unsigned int>(o.list.begin(), o.list.end()))
  {
  }
  Collision() :
    list(std::list<unsigned int>())
  {}
  ~Collision()
  {}
};

#endif				// __COLLISION_COMPONENT_HPP__
