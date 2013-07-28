#ifndef				__COLOR_EASING_COMPONENT_HPP__
# define			__COLOR_EASING_COMPONENT_HPP__

#include			"Color.hpp"
#include			"ComponentManager.hpp"

struct				ColorEasing
{
public:
  float				time;
  float				timeOrigin;
  Color				color;
  Color				colorOrigin;

public:
  void				setEasing(const Color & c, float _time)
  {
    color = c;
    time = _time;
    timeOrigin = _time;
  }

};

#endif				// __COLOR_EASING_COMPONENT_HPP__
