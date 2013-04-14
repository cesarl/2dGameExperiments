#include				"BoundingBox.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

BoundingBox::BoundingBox(Entity *entity) :
  AComponent(entity, T_BOUNDING_BOX),
  width_(0),
  height_(0),
  collidable_(true)
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
  Position				*p1;
  Position				*p2;
  const BoundingBox			*bb1;
  BoundingBox				*bb2;

  if (!this->collidable_ || !BOUNDING_BOX(o)->isCollidable())
    return false;
  p1 = POSITION(this->entity);
  p2 = POSITION(o);
  bb1 = this;
  bb2 = BOUNDING_BOX(o);

  if (p1->x > p2->x + bb2->getWidth() ||
      p1->x + bb1->getWidth() < p2->x ||
      p1->y > p2->y + bb2->getHeight() ||
      p1->y + bb1->getHeight() < p2->y)
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
