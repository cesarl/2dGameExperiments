#ifndef				__COLOR_EASING_COMPONENT_HPP__
# define			__COLOR_EASING_COMPONENT_HPP__

#include			"Color.hpp"
#include			"ComponentManager.hpp"

struct				ColorEasing
{
public:
  float				time;
  float				duration;
  Color				color;
  Color				colorOrigin;

public:
  void				setEasing(const Color & c, float _time, unsigned int entity)
  {
    color = c;
    time = 0.0f;
    duration = _time;
    colorOrigin = *(ComponentManager::getInstance().getComponent<Color>(entity));
  }

};

#endif				// __COLOR_EASING_COMPONENT_HPP__
