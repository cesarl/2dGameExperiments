#ifndef				__COLOR_EASING_SYSTEM_HPP__
# define			__COLOR_EASING_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

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

    color->r = color->r + (eas->color.r - color->r) * time;
    color->g = color->g + (eas->color.g - color->g) * time;
    color->b = color->b + (eas->color.b - color->b) * time;
    color->a = color->a + (eas->color.a - color->a) * time;

    eas->time = (float)eas->time - time;

    std::cout << color->r << " " << color->g << " " << color->b << " " << color->a << " " << eas->time << " " << time <<std::endl;

    if (eas->time <= 0.0f)
      ComponentManager::getInstance().removeComponent<ColorEasing>(entity);
  }

private:
};

// template<typename Type, typename DeltaType = float>
// Type Lerp(Type src, Type dest, DeltaType delta)
// {
//   return src + (dest - src) * delta;
// }

// Lerp(currentColor, destColor, delta)

#endif				// __COLOR_EASING_SYSTEM_HPP__
