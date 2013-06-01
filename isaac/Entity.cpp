#include				"Entity.hh"
#include				"ComponentTypes.hh"

Entity::Entity()
{
  this->drawable_ = NULL;
  srand(time(0) + rand());
  this->seed_ = rand();
  this->enable_ = true;
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

void					Entity::removeComponent(int type)
{
  t_iter				it;
  t_prio_iter				prio_it;

  it = this->list_.find(type);
  if (it == this->list_.end())
    return;
  if (this->drawable_ == it->second)
    this->drawable_ = NULL;
  prio_it = this->updatePriorityList_.begin();
  while (prio_it != this->updatePriorityList_.end())
    {
      if (prio_it->second == it->second)
	break;
      ++prio_it;
    }
  if (prio_it != this->updatePriorityList_.end())
    this->updatePriorityList_.erase(prio_it);
  delete it->second;
  this->list_.erase(it);
}

bool					Entity::hasComponent(int type) const
{
  t_const_iter				it;

  it = this->list_.find(type);
  if (it != this->list_.end())
    return true;
  return false;
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

void					Entity::serialize(std::ofstream *file)
{
  t_iter				it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      it->second->serialize(file);
      ++it;
    }
  int zero = 0;

  file->write(reinterpret_cast<const char *>(&zero), sizeof(0));
}

void					Entity::unserialize(std::ifstream *file)
{
  int					type;

  do
    {
      file->read(reinterpret_cast<char*>(&type), sizeof(int));
      if (type == 0)
	return;
      unserializeComponent(type, this, file);
    }
  while (type != 0);
}


void					Entity::generate(int seed)
{
  this->seed_ = seed;
}

void					Entity::enable()
{
  this->enable_ = true;
}

void					Entity::disable()
{
  this->enable_ = false;
}

bool					Entity::isEnable()
{
  return this->enable_;
}
