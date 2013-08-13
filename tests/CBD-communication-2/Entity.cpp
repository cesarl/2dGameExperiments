#include			"Entity.hh"

Entity::Entity(std::string const & name) : name_(name)
{
  std::cout << "An entity named " << name << " has been created" << std::endl;
}

Entity::~Entity()
{}

void				Entity::update()
{
  t_iter			it;

  std::cout << "Entity " << this->name_ << " start update" << std::endl;
  it = this->list_.begin();
  while (it != this->list_.end())
    {
      (*it)->update();
      ++it;
    }
  std::cout << "// Entity " << this->name_ << " end update" << std::endl;
}

void				Entity::addComponent(AComponent *component)
{
  this->list_.push_back(component);
  component->setEntity(this);
  std::cout << "A component of type " << component->getType() << " has been added to " << this->name_ << std::endl;
}

AComponent			*Entity::getComponent(int type) const
{
  t_const_iter			it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      if ((*it)->getType() == type)
	return *it;
      ++it;
    }
  return NULL;
}

const std::string		&Entity::getName() const
{
  return this->name_;
}
