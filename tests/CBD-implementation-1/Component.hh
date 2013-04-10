#ifndef					__COMPONENT_HH__
# define				__COMPONENT_HH__

#include				"Entity.hh"
#include				"IdManager.hh"

class					Entity;
class					AComponent;

struct					DataComponent
{
  int					updatePriority;
  int					drawPriority;
  Entity				*entity;
  AComponent				*component;
  int					entityId;
  int					typeId;
  double				updateTimestamp;

  DataComponent(int typeId, AComponent *component);
  virtual ~DataComponent();
};

class					AComponent
{
public:
  virtual void				init(Entity *entity) = 0;
  virtual void				update(Entity *entity, double time = 0) = 0;
  virtual ~AComponent(){};
  int					getTypeId() const
  {
    return this->typeId_;
  }
protected:
  AComponent()
  {
    this->typeId_ = IdManager::getInstance()->newId();
  }
  int					typeId_;
};

#endif					// __COMPONENT_HH__
