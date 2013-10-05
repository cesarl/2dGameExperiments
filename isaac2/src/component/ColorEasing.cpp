#include "ColorEasingSystem.hpp"
#include "EntityData.hpp"

void				ColorEasing::setEasing(const Color & c, float _time, EntityData &entity)
  {
    color = c;
    time = 0.0f;
    duration = _time;
    colorOrigin = *(entity.getComponent<Color>());
  }
