#ifndef					__COMPONENT_HH__
# define				__COMPONENT_HH__

#include				"Entity.hh"
#include				"IdManager.hh"

class					Entity;

class					AComponent
{
public:
  virtual void				update(double time = 0) = 0;
  virtual void				draw() = 0;
  virtual ~AComponent();
  AComponent(Entity *entity, int typeId, int updatePriority = 0, int drawPriority = 0);
public:
  int					updatePriority;
  int					drawPriority;
  Entity				*entity;
  int					entityId;
  int					typeId;
  double				updateTimestamp;
};

#endif					// __COMPONENT_HH__
