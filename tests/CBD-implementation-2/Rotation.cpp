#include				"Rotation.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

Rotation::Rotation(Entity *entity) : AComponent(entity, T_ROTATION)
{
  this->angle = 0;
}

Rotation::~Rotation()
{}

void					Rotation::update(double time)
{
  (void)time;
}

void					Rotation::draw()
{}
