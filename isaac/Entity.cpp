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
  int					x;
  int					y;
  int					r;
  Position				*position;
  Rotation				*rotation;

  position = POSITION(this);
  rotation = ROTATION(this);

  x = (int)(position->x);
  y = (int)(position->y);
  r = (int)(rotation->angle * 180 / M_PI);


  file->write(reinterpret_cast<const char *>(&this->seed_), sizeof(this->seed_));
  file->write(reinterpret_cast<const char *>(&x), sizeof(x));
  file->write(reinterpret_cast<const char *>(&y), sizeof(y));
  file->write(reinterpret_cast<const char *>(&r), sizeof(r));
}

void					Entity::unserialize(std::ifstream *file)
{
  int				posx;
  int				posy;
  int				rot;
  int				seed;

  file->read(reinterpret_cast<char*>(&seed), sizeof(int));
  file->read(reinterpret_cast<char*>(&posx), sizeof(int));
  file->read(reinterpret_cast<char*>(&posy), sizeof(int));
  file->read(reinterpret_cast<char*>(&rot), sizeof(int));
  this->generate(seed);
  POSITION(this)->setPos(posx, posy);
  ROTATION(this)->angle = rot * M_PI / 180;
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
