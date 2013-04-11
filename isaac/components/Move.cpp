#include				"Move.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer


Move::Move(Entity *entity) : AComponent(entity, T_MOVE, 1)
{
  POSITION(entity);
  this->vx = 0;
  this->vy = 0;
  this->frictionX = 0;
  this->frictionY = 0;
  this->gravityX = 0;
  this->gravityY = 0;
}

Move::~Move()
{}

void					Move::update(double time)
{
  Position				*position;

  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;

  position = POSITION(this->entity);
  this->vx -= this->frictionX;
  this->vy -= this->frictionY;
  if (this->vx < 0)
    this->vx = 0;
  if (this->vy < 0)
    this->vy = 0;
  this->vx += this->gravityX;
  this->vy += this->gravityY;
  position->x += this->vx * this->dirX_;
  position->y += this->vy * this->dirY_;
}

void					Move::draw()
{}

void					Move::setDirection(double x, double y)
{
  this->dirX_ = 0;
  this->dirY_ = 0;
  if (x > 0)
    this->dirX_ = 1;
  else if (x < 0)
    this->dirX_ = -1;
  if (y > 0)
    this->dirY_ = 1;
  else if (y < 0)
    this->dirY_ = -1;
  this->vx = fabs(x);
  this->vy = fabs(y);
}

void					Move::setDirectionX(double x)
{
  this->dirX_ = 0;
  if (x > 0)
    this->dirX_ = 1;
  else if (x < 0)
    this->dirX_ = -1;
  this->vx = fabs(x);
}

void					Move::setDirectionY(double y)
{
  this->dirY_ = 0;
  if (y > 0)
    this->dirY_ = 1;
  else if (y < 0)
    this->dirY_ = -1;
  this->vy = fabs(y);
}

void					Move::setFriction(double x, double y)
{
  this->frictionX = fabs(x);
  this->frictionY = fabs(y);
}
