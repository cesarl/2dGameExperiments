#include				"Death.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

Death::Death(Entity *entity) :
  AComponent(entity, T_DEATH),
  dead_(false)
{
}

Death::~Death()
{}

void					Death::update(double time)
{
  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;
}

void					Death::draw()
{}

bool					Death::isDead() const
{
  return this->dead_;
}

void					Death::setDead(bool dead)
{
  this->dead_ = dead;
}

void					Death::kill()
{
  this->dead_ = true;
}

void					Death::serialize(std::ofstream *file)
{
  int					type = T_DEATH;

  file->write(reinterpret_cast<const char *>(&type), sizeof(type));
  file->write(reinterpret_cast<const char *>(&this->dead_), sizeof(bool));
}

void					Death::unserialize(std::ifstream *file)
{
  file->read(reinterpret_cast<char *>(&this->dead_), sizeof(bool));
}
