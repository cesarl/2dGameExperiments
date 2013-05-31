#include				"Health.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

Health::Health(Entity *entity) : AComponent(entity, T_HEALTH), health_(10), delay_(0), delayCounter_(0)
{

}

Health::~Health()
{}

void					Health::update(double time)
{
  if (this->updateTimestamp == time)
    return;
}

void					Health::draw()
{}

void					Health::setHealth(int health)
{
  this->health_ = health;
}

int					Health::getHealth() const
{
  return this->health_;
}

void					Health::impactDamage(Entity *e)
{
  if (al_get_time() - this->delayCounter_ < this->delay_)
    {
      this->delayCounter_ = al_get_time();
      return;
    }
  this->delayCounter_ = al_get_time();

  this->health_ -= DAMAGE(e)->getMagnitude();
  if (this->health_ <= 0 && this->entity->hasComponent(T_DEATH))
    {
      DEATH(this->entity)->kill();
    }
}

void					Health::setDelay(double delay)
{
  this->delay_ = delay;
}

void					Health::serialize(std::ofstream *file)
{
  int					type = T_HEALTH;

  file->write(reinterpret_cast<const char *>(&type), sizeof(type));
  file->write(reinterpret_cast<const char *>(&this->health_), sizeof(int));
  file->write(reinterpret_cast<const char *>(&this->delay_), sizeof(double));
}

void					Health::unserialize(std::ifstream *file)
{
  file->read(reinterpret_cast<char *>(&this->health_), sizeof(int));
  file->read(reinterpret_cast<char *>(&this->delay_), sizeof(double));
}
