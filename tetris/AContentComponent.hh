#ifndef					__ACONTENT_COMPONENT_HH__
# define				__ACONTENT_COMPONENT_HH__

#include				"Entity.hh"
#include				"ContentComponentTypes.hh"

class					Entity;

class					AContentComponent
{
public:
  AContentComponent(e_contentComponentType type);
  virtual ~AContentComponent();
  virtual void				update(Entity *entity, ALLEGRO_EVENT *event) = 0;
  virtual void				draw(Entity *entity) = 0;
  void					setPriority(unsigned int priority);
  unsigned int				getPriority() const;
  int					getType() const;
protected:
  unsigned int				priority_;
  e_contentComponentType		type_;
};

#endif					// __ACONTENT_COMPONENT_HH__
