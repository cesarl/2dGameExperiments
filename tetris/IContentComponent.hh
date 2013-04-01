#ifndef					__ICONTENT_COMPONENT_HH__
# define				__ICONTENT_COMPONENT_HH__

#include				"Entity.hh"

class					Entity;

class					IContentComponent
{
public:
  virtual ~IContentComponent(){};
  virtual void				update(Entity *entity, ALLEGRO_EVENT *event) = 0;
  virtual void				draw(Entity *entity) = 0;
};

#endif					// __ICONTENT_COMPONENT_HH__
