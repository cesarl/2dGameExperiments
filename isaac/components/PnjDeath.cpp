#include				"PnjDeath.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

PnjDeath::PnjDeath(Entity *entity) :
  Death(entity)
{
}

PnjDeath::~PnjDeath()
{}

void					PnjDeath::update(double time)
{
  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;
}

void					PnjDeath::draw()
{}

bool					PnjDeath::isDead() const
{
  return this->dead_;
}

void					PnjDeath::setDead(bool dead)
{
  this->dead_ = dead;
}

void					PnjDeath::kill()
{
  ROTATION_FORCE(this->entity)->launch(0.3, 0.05);
  this->dead_ = true;
}

// void					PnjDeath::serialize(std::ofstream *file)
// {
//   int					type = T_PNJ_DEATH;

//   file->write(reinterpret_cast<const char *>(&type), sizeof(type));
// }
