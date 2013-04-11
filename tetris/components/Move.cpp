#include				"Move.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer


Move::Move(Entity *entity) : AComponent(entity, T_MOVE, 1)
{
  POSITION(entity);
  this->vx = 3;
  this->vy = 3;
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
  this->vx += this->gravityX;
  this->vy += this->gravityY;
  position->x += this->vx;
  position->y += this->vy;
}

void					Move::draw()
{}
