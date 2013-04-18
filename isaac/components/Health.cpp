#include				"Health.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

Health::Health(Entity *entity) : AComponent(entity, T_HEALTH), health_(10)
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
  this->health_ -= DAMAGE(e)->getMagnitude();
  if (this->health_ <= 0 && this->entity->hasComponent(T_DEATH))
    {
      DEATH(this->entity)->kill();
    }
}
