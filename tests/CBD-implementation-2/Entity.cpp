#include				"Entity.hh"

Entity::Entity()
{
  this->drawable_ = NULL;
}

Entity::~Entity()
{
  t_iter				it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      delete it->second;
      ++it;
    }
  this->list_.clear();
  this->updatePriorityList_.clear();
}

int					Entity::getId() const
{
  return this->id_;
}

void					Entity::setId(int id)
{
  this->id_ = id;
}

AComponent				*Entity::getComponent(int type) const
{
  t_const_iter				it;

  it = this->list_.find(type);
  if (it != this->list_.end())
    return 0;
  return it->second;
}

void					Entity::addComponent(AComponent *component)
{
  t_prio_iter				it;

  this->id_ = IdManager::getInstance()->newId();
  this->list_.insert(t_pair(component->typeId, component));

  if (component->updatePriority > 0)
    {
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
    }
  if (component->drawPriority > 0)
    {
      if (!this->drawable_)
	this->drawable_ = component;
      else if (this->drawable_->drawPriority < component->drawPriority)
	this->drawable_ = component;
    }
}

void					Entity::update()
{
  t_prio_iter				it;
  double				time = al_get_time();

  it = this->updatePriorityList_.begin();
  while (it != this->updatePriorityList_.end())
    {
      it->second->update(time);
      ++it;
    }
}

void					Entity::draw()
{
  if (this->drawable_)
    this->drawable_->draw();
}
