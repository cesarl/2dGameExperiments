#include				"PnjHealth.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

PnjHealth::PnjHealth(Entity *entity) : Health(entity)
{
}

PnjHealth::~PnjHealth()
{}

void					PnjHealth::impactDamage(Entity *e)
{
  if (al_get_time() - this->delayCounter_ < this->delay_)
    {
      this->delayCounter_ = al_get_time();
      return;
    }
  this->health_ -= DAMAGE(e)->getMagnitude();
  if (this->health_ <= 0 && this->entity->hasComponent(T_DEATH))
    {
      DEATH(this->entity)->kill();
    }
  else
    VISIBILITY(this->entity)->blink(30, 0.2);
}

// void					PnjHealth::serialize(std::ofstream *file)
// {
//   int					type = T_PNJ_HEALTH;

//   file->write(reinterpret_cast<const char *>(&type), sizeof(type));
// }
