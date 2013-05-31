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

void					Rotation::serialize(std::ofstream *file)
{
  int					type = T_ROTATION;

  file->write(reinterpret_cast<const char *>(&type), sizeof(type));
  file->write(reinterpret_cast<const char *>(&this->angle), sizeof(float)
);
}

void					Rotation::unserialize(std::ifstream *file)
{
  file->read(reinterpret_cast<char *>(&this->angle), sizeof(float));
}
