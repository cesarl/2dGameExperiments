#include				"Entity.hh"

Entity::Entity() : content_(NULL)
{}

Entity::Entity(IContentComponent *content) : content_(content)
{}

Entity::~Entity()
{}

void					Entity::update(ALLEGRO_EVENT *event)
{
  if (this->content_)
    this->content_->update(this, event);
}

void					Entity::draw()
{
  if (this->content_)
    this->content_->draw(this);
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

void					Entity::setContentComponent(IContentComponent *content)
{
  this->content_ = content;
}

IContentComponent			*Entity::getContentComponent() const
{
  return this->content_;
}

void					Entity::deleteContentComponent()
{
  if (this->content_)
    delete this->content_;
  this->content_ = NULL;
}
