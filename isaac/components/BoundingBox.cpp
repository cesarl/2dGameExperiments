#include				"BoundingBox.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

BoundingBox::BoundingBox(Entity *entity) :
  AComponent(entity, T_BOUNDING_BOX),
  width_(0),
  height_(0),
  collidable_(true),
  marginX_(0),
  marginY_(0)
{
  POSITION(entity);
}

BoundingBox::~BoundingBox()
{}

void					BoundingBox::update(double time)
{
  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;
}

void					BoundingBox::draw()
{}

void					BoundingBox::setWidth(int width)
{
  this->width_ = width;
}

int					BoundingBox::getWidth() const
{
  return this->width_;
}

void					BoundingBox::setHeight(int height)
{
  this->height_ = height;
}

int					BoundingBox::getHeight() const
{
  return this->height_;
}

bool					BoundingBox::collide(Entity *o) const
{
  const BoundingBox			*bb1;
  BoundingBox				*bb2;

  if (!this->collidable_ || !BOUNDING_BOX(o)->isCollidable())
    return false;
  bb1 = this;
  bb2 = BOUNDING_BOX(o);

  if (bb1->getX() > bb2->getXX() ||
      bb1->getXX() < bb2->getX() ||
      bb1->getY() > bb2->getYY() ||
      bb1->getYY() < bb2->getY())
    return false;
  return true;
}

void					BoundingBox::setDimension(int width, int height)
{
  this->width_ = width;
  this->height_ = height;
}

bool					BoundingBox::isCollidable() const
{
  return this->collidable_;
}

void					BoundingBox::setCollidable(bool val)
{
  this->collidable_ = val;
}

void					BoundingBox::setMargin(int x, int y)
{
  this->marginX_ = x;
  this->marginY_ = y;
}

void					BoundingBox::setMarginX(int x)
{
  this->marginX_ = x;
}

void					BoundingBox::setMarginY(int y)
{
  this->marginY_ = y;
}

int					BoundingBox::getMarginX() const
{
  return this->marginX_;
}

int					BoundingBox::getMarginY() const
{
  return this->marginY_;
}

int					BoundingBox::getX() const
{
  return POSITION(this->entity)->x + this->marginX_;
}

int					BoundingBox::getXX() const
{
  return POSITION(this->entity)->x + this->marginX_ + this->width_;
}

int					BoundingBox::getY() const
{
  return POSITION(this->entity)->y + this->marginY_;
}

int					BoundingBox::getYY() const
{
  return POSITION(this->entity)->y + this->marginY_ + this->height_;
}

int					BoundingBox::getCenterX() const
{
  return (this->width_ / 2) + this->marginX_ + POSITION(this->entity)->x;
}

int					BoundingBox::getCenterY() const
{
  return (this->height_ / 2) + this->marginY_ + POSITION(this->entity)->y;
}

void					BoundingBox::unserialize(std::ifstream *file)
{
  file->read(reinterpret_cast<char*>(&(this->width_)), sizeof(int));
  file->read(reinterpret_cast<char*>(&(this->height_)), sizeof(int));
  file->read(reinterpret_cast<char*>(&(this->collidable_)), sizeof(bool));
  file->read(reinterpret_cast<char*>(&(this->marginX_)), sizeof(int));
  file->read(reinterpret_cast<char*>(&(this->marginY_)), sizeof(int));
}

void					BoundingBox::serialize(std::ofstream *file)
{
  int					type = T_BOUNDING_BOX;

  file->write(reinterpret_cast<const char *>(&type), sizeof(type));
  file->write(reinterpret_cast<const char *>(&this->width_), sizeof(this->width_));
  file->write(reinterpret_cast<const char *>(&this->height_), sizeof(this->height_));
  file->write(reinterpret_cast<const char *>(&this->collidable_), sizeof(this->collidable_));
  file->write(reinterpret_cast<const char *>(&this->marginX_), sizeof(this->marginX_));
  file->write(reinterpret_cast<const char *>(&this->marginY_), sizeof(this->marginY_));
}
