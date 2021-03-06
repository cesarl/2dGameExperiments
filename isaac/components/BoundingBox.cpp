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

void					BoundingBox::unserialize(std::ifstream &file)
{
  Archive::unserialize(file, this->width_);
  Archive::unserialize(file, this->height_);
  Archive::unserialize(file, this->collidable_);
  Archive::unserialize(file, this->marginX_);
  Archive::unserialize(file, this->marginY_);
}

void					BoundingBox::serialize(std::ofstream &file)
{
  int					type = T_BOUNDING_BOX;

  Archive::serialize(file, type);
  Archive::serialize(file, this->width_);
  Archive::serialize(file, this->height_);
  Archive::serialize(file, this->collidable_);
  Archive::serialize(file, this->marginX_);
  Archive::serialize(file, this->marginY_);
}
