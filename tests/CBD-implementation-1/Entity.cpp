#include				"Entity.hh"

Entity::Entity()
{}

Entity::~Entity()
{}

int					Entity::getId() const
{
  return this->id_;
}

void					Entity::setId(int id)
{
  this->id_ = id;
}

DataComponent				*Entity::getComponent(int type) const
{
  t_const_iter				it;

  it = this->list_.find(type);
  if (it == this->list_.end())
    return 0;
  return it->second;
}

void					Entity::addComponent(DataComponent *component)
{
  t_prio_iter				it;

  component->entity = this;
  this->list_.insert(t_pair(component->typeId, component));
  it = this->updatePriorityList_.begin();
  while (it != this->updatePriorityList_.end())
    {
      if (it->second->updatePriority <= component->updatePriority)
	break;
      ++it;
    }
  if (it != this->updatePriorityList_.end())
    {
      this->updatePriorityList_.insert(it, t_pair(component->updatePriority, component));
    }
 else
   this->updatePriorityList_.push_back(t_pair(component->updatePriority, component));
  // Component				*component;

  // component = System::getInstance()->createComponent(type);
  // this->list_.insert(t_pair(type, component));
  // return component;
}

void					Entity::update()
{
  t_iter				it;
  double				time = al_get_time();

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      it->second->component->update(this, time);
      ++it;
    }
}
