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
  this->maxSpeed_ = 10;
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
  if (this->vx > this->maxSpeed_)
    this->vx = this->maxSpeed_;
  if (this->vy > this->maxSpeed_)
    this->vy = this->maxSpeed_;
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

void					Move::incDirectionX(double x)
{
  this->vx *= this->dirX_;
  this->vx += x;
  if (this->vx > 0)
    this->dirX_ = 1;
  else if (this->vx < 0)
    {
      this->dirX_ = -1;
      this->vx = fabs(this->vx);
    }
  else
    this->dirX_ = 0;
}

void					Move::incDirectionY(double y)
{
  this->vy *= this->dirY_;
  this->vy += y;
  if (this->vy > 0)
    this->dirY_ = 1;
  else if (this->vy < 0)
    {
      this->dirY_ = -1;
      this->vy = fabs(this->vy);
    }
  else
    this->dirY_ = 0;
}

void					Move::setFriction(double x, double y)
{
  this->frictionX = fabs(x);
  this->frictionY = fabs(y);
}

double					Move::getDirectionX() const
{
  return this->vx * this->dirX_;
}

double					Move::getDirectionY() const
{
  return this->vy * this->dirY_;
}

double					Move::getDirection() const
{
  return atan2(this->vy * this->dirY_, this->vx * this->dirX_);
}

void					Move::reverseOneAxe(int x, int y, double multiply)
{
  if (x > y)
    {
      this->dirX_ *= -1;
      this->vx *= multiply;
    }
  else
    {
      this->dirY_ *= -1;
      this->vy *= multiply;
    }
}

void					Move::setMaxSpeed(double val)
{
  this->maxSpeed_ = val;
}

void					Move::serialize(std::ofstream *file)
{
  int					type = T_MOVE;

  file->write(reinterpret_cast<const char *>(&type), sizeof(type));
  file->write(reinterpret_cast<const char *>(&this->vx), sizeof(double));
  file->write(reinterpret_cast<const char *>(&this->vy), sizeof(double));
  file->write(reinterpret_cast<const char *>(&this->gravityX), sizeof(double));
  file->write(reinterpret_cast<const char *>(&this->gravityY), sizeof(double));
  file->write(reinterpret_cast<const char *>(&this->frictionX), sizeof(double));
  file->write(reinterpret_cast<const char *>(&this->frictionY), sizeof(double));
  file->write(reinterpret_cast<const char *>(&this->dirX_), sizeof(int));
  file->write(reinterpret_cast<const char *>(&this->dirY_), sizeof(int));
  file->write(reinterpret_cast<const char *>(&this->maxSpeed_), sizeof(double));
}

void					Move::unserialize(std::ifstream *file)
{
  file->read(reinterpret_cast<char *>(&this->vx), sizeof(double));
  file->read(reinterpret_cast<char *>(&this->vy), sizeof(double));
  file->read(reinterpret_cast<char *>(&this->gravityX), sizeof(double));
  file->read(reinterpret_cast<char *>(&this->gravityY), sizeof(double));
  file->read(reinterpret_cast<char *>(&this->frictionX), sizeof(double));
  file->read(reinterpret_cast<char *>(&this->frictionY), sizeof(double));
  file->read(reinterpret_cast<char *>(&this->dirX_), sizeof(int));
  file->read(reinterpret_cast<char *>(&this->dirY_), sizeof(int));
  file->read(reinterpret_cast<char *>(&this->maxSpeed_), sizeof(double));
}
