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
  component->entity = this;
  this->list_.insert(t_pair(component->type, component));
  // Component				*component;

  // component = System::getInstance()->createComponent(type);
  // this->list_.insert(t_pair(type, component));
  // return component;
}

void					Entity::update()
{
  t_iter				it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      it->second->component->update(this);
      ++it;
    }
}
