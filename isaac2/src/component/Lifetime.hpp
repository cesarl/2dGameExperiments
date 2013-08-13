#ifndef				__LIFETIME_COMPONENT_HPP__
# define			__LIFETIME_COMPONENT_HPP__

#include			"Component.hpp"

struct				Lifetime : public Component<Lifetime>
{
  float				time;
};

#endif				// __LIFETIME_COMPONENT_HPP__
