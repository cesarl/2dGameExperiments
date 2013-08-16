#ifndef				__SMELL_POSITION_COMPONENT_HPP__
# define			__SMELL_POSITION_COMPONENT_HPP__

#include			"Component.hpp"

struct				SmellPosition : public Component<Position>
{
  bool				active;

  SmellPosition() :
    active(true)
  {}
};

#endif				// __SMELL_POSITION_COMPONENT_HPP__
