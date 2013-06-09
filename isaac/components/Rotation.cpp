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

void					Rotation::serialize(std::ofstream &file)
{
  int					type = T_ROTATION;

  Archive::serialize(file, type);
  Archive::serialize(file, this->angle);
}

void					Rotation::unserialize(std::ifstream &file)
{
  Archive::unserialize(file, this->angle);
}
