#ifndef				__COLOR_EASING_SYSTEM_HPP__
# define			__COLOR_EASING_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"
#include			"lerp.hpp"

class				ColorEasingSystem : public System
{
public:
  virtual ~ColorEasingSystem(){};
  ColorEasingSystem()
  {}
  void				init()
  {
    require<ColorEasing>();
    require<Color>();
  }


  virtual void			update(unsigned int entity, float time, const ALLEGRO_EVENT &)
  {
    ColorEasing			*eas = ComponentManager::getInstance().getComponent<ColorEasing>(entity);
    Color			*color = ComponentManager::getInstance().getComponent<Color>(entity);

    // color->r = eas->colorOrigin.r + (eas->color.r - eas->colorOrigin.r) * eas->time;
    // color->g = eas->colorOrigin.g + (eas->color.g - eas->colorOrigin.g) * eas->time;
    // color->b = eas->colorOrigin.b + (eas->color.b - eas->colorOrigin.b) * eas->time;
    // color->a = eas->colorOrigin.a + (eas->color.a - eas->colorOrigin.a) * eas->time;

    *color = Utils::lerp<Color>(eas->colorOrigin, eas->color, eas->duration, eas->time);

    eas->time = (float)eas->time + time;

    //std::cout << color->r << " " << color->g << " " << color->b << " " << color->a << " " << eas->time << " " << time << std::endl;

    if (eas->time >= eas->duration)
      ComponentManager::getInstance().removeComponent<ColorEasing>(entity);
  }

private:
};


// Lerp(currentColor, destColor, delta)

#endif				// __COLOR_EASING_SYSTEM_HPP__
