#include				"Position.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

Position::Position(Entity *entity) : AComponent(entity, T_POSITION)
{
  this->x = 10;
  this->y = 10;
}

Position::~Position()
{}

void					Position::update(double time)
{
  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;
}

void					Position::draw()
{}

int					Position::getX() const
{
  return this->x;
}

void					Position::setPos(double x, double y)
{
  this->x = x;
  this->y = y;
}
