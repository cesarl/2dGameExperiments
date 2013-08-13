#include			"Entity.hh"

Entity::Entity(int x, int y, int radius) :
  x_(x),
  y_(y),
  radius_(radius)
{}

Entity::~Entity()
{}

void				Entity::move()
{
}

void				Entity::draw()
{
  al_draw_filled_circle(this->x_, this->y_, this->radius_, this->color_);
}

int				Entity::getX() const
{
  return this->x_;
}

int				Entity::getY() const
{
  return this->y_;
}

void				Entity::setX(int x)
{
  this->x_= x;
}

void				Entity::setY(int y)
{
  this->y_ = y;
}

int				Entity::getRadius() const
{
  return this->radius_;
}

void				Entity::setRadius(int radius)
{
  this->radius_ = radius;
}

ALLEGRO_COLOR			Entity::getColor() const
{
  return this->color_;
}

int				Entity::getHexColor() const
{
  return this->hexColor_;
}

void				Entity::setColor(ALLEGRO_COLOR color)
{
  this->color_ = color;
}

void				Entity::setHexColor(int color)
{
  this->hexColor_ = color;
  this->p_hexColorToAlColor();
}

void				Entity::p_hexColorToAlColor()
{
  this->color_ = al_map_rgb((this->hexColor_ >> 16) & 0xFF,
			   (this->hexColor_ >> 8) & 0xFF,
			   this->hexColor_ & 0xFF);
}

bool				Entity::getVisible() const
{
  return this->visible_;
}

void				Entity::setVisible(bool visible)
{
  this->visible_ = visible;
}
