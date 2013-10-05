#ifndef				__COLOR_EASING_COMPONENT_HPP__
# define			__COLOR_EASING_COMPONENT_HPP__

#include			"Color.hpp"

struct              EntityData;

struct				ColorEasing : public Component<ColorEasing>
{
public:
  float				time;
  float				duration;
  Color				color;
  Color				colorOrigin;

public:
  void				setEasing(const Color & c, float _time, EntityData &entity);
};

#endif				// __COLOR_EASING_COMPONENT_HPP__
