#include				"Position.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

Position::Position(Entity *entity) : AComponent(entity, T_POSITION, 15)
{
  this->x = 0;
  this->y = 0;
  this->z = 0;
  this->postx_ = 0;
  this->posty_ = 0;
}

Position::~Position()
{}

void					Position::update(double time)
{
  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;
  this->postx_ = this->x;
  this->posty_ = this->y;
}

void					Position::draw()
{}

int					Position::getX() const
{
  return this->x;
}

void					Position::setPos(double x, double y, double z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

void					Position::reversePos()
{
  this->x = this->postx_;
  this->y = this->posty_;
}


void					Position::serialize(std::ofstream *file)
{
  int					type = T_POSITION;

  file->write(reinterpret_cast<const char *>(&type), sizeof(type));
  file->write(reinterpret_cast<const char *>(&this->x), sizeof(this->x));
  file->write(reinterpret_cast<const char *>(&this->y), sizeof(this->y));
  file->write(reinterpret_cast<const char *>(&this->z), sizeof(this->z));
}

void					Position::unserialize(std::ifstream *file)
{
  file->read(reinterpret_cast<char *>(&this->x), sizeof(this->x));
  file->read(reinterpret_cast<char *>(&this->y), sizeof(this->y));
  file->read(reinterpret_cast<char *>(&this->z), sizeof(this->z));
}
