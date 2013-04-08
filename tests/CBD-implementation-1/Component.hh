#ifndef					__COMPONENT_HH__
# define				__COMPONENT_HH__

#include				"Entity.hh"
#include				"IdManager.hh"

class					Entity;
class					AComponent;

struct					DataComponent
{
  int					type;
  int					priority;
  Entity				*entity;
  AComponent				*component;
  int					entityId;
  int					typeId;
};

class					AComponent
{
public:
  virtual void				init(Entity *entity) = 0;
  virtual void				update(Entity *entity) = 0;
  // template				<typename T>
  // virtual T				*operator()(Entity *entity) = 0;
  virtual ~AComponent(){};
protected:
  AComponent()
  {
    this->typeId_ = IdManager::getInstance()->newId();
  }
  int					typeId_;
};

#endif					// __COMPONENT_HH__
