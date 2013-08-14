#ifndef				__SPRITE_COMPONENT_HPP__
# define			__SPRITE_COMPONENT_HPP__

#include			"Component.hpp"

struct				Sprite : public Component<Sprite>
{
  unsigned int			index;
  int				cycleCounter;
  double			timeCounter;
  AnimationPtr			animation;

  Sprite() :
    index(0),
    cycleCounter(0),
    timeCounter(0.0f)
  {}

  Sprite			&operator=(const Sprite &o )
  {
    this->animation = o.animation;
    return *this;
  }
};

#endif				// __SPRITE_COMPONENT_HPP__
