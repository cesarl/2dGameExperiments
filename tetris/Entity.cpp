#include				"Entity.hh"

Entity::Entity() : x_(0),
		   y_(0),
		   width_(0),
		   height_(0),
		   visible_(true)
{}

Entity::Entity(AContentComponent *content) : x_(0),
					     y_(0),
					     width_(0),
					     height_(0),
					     visible_(true)
{
  if (content)
    this->setContentComponent(content);
}

Entity::~Entity()
{}

void					Entity::update(ALLEGRO_EVENT *event)
{
  t_iter				it;

  it = this->content_.begin();
  while (it != this->content_.end())
    {
      (*it)->update(this, event);
      ++it;
    }
}

void					Entity::draw()
{
  t_iter				it;

  if (!this->visible_)
    return;
  it = this->content_.begin();
  while (it != this->content_.end())
    {
      (*it)->draw(this);
      ++it;
    }
}

void					Entity::setPos(float x, float y)
{
  this->x_ = x;
  this->y_ = y;
}

void					Entity::setX(float x)
{
  this->x_ = x;
}

void					Entity::setY(float y)
{
  this->y_ = y;
}

void					Entity::setWidth(float width)
{
  this->width_ = width;
}

void					Entity::setHeight(float height)
{
  this->height_ = height;
}

void					Entity::setVisible(bool visible)
{
  this->visible_ = visible;
}

float					Entity::getX() const
{
  return this->x_;
}

float					Entity::getY() const
{
  return this->y_;
}

float					Entity::getWidth() const
{
  return this->width_;
}

float					Entity::getHeight() const
{
  return this->height_;
}

void					Entity::setContentComponent(AContentComponent *content, unsigned int priority)
{
  t_iter				it;

  if (priority == 0)
    {
    this->content_.push_back(content);
    content->setPriority(priority);
    return;
    }
  it = this->content_.begin();
  while (it != this->content_.end())
    {
      if ((*it)->getPriority() < priority)
	break;
      ++it;
    }
  if (it != this->content_.end())
    this->content_.insert(it, content);
  else
    this->content_.push_back(content);
  content->setPriority(priority);
}

AContentComponent			*Entity::getContentComponent(e_contentComponentType type) const
{
  t_const_iter				it;

  it = this->content_.begin();
  if (type == -1)
    return *it;
  while (it != this->content_.end())
    {
      if ((*it)->getType() == type)
	return *it;
      ++it;
    }
  return NULL;
}

bool					Entity::getVisible() const
{
  return this->visible_;
}

// todo
// delete &| remove component

// void					Entity::deleteContentComponent()
// {
//   if (this->content_)
//     delete this->content_;
//   this->content_ = NULL;
// }
