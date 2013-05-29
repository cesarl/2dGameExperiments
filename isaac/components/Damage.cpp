#include				"Damage.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

Damage::Damage(Entity *entity) :
  AComponent(entity, T_DAMAGE),
  magnitude_(0),
  damageNb_(1),
  delay_(1),
  delayCounter_(0)
{
}

Damage::~Damage()
{}

void					Damage::update(double time)
{
  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;
}

void					Damage::draw()
{}

void					Damage::setMagnitude(int magnitude)
{
  this->magnitude_ = magnitude;
}

void					Damage::setDamageNb(int damageNb)
{
  this->damageNb_ = damageNb;
}

void					Damage::setDelay(double delay)
{
  this->delay_ = delay;
}

int					Damage::getMagnitude() const
{
  return this->magnitude_;
}

int					Damage::getDamageNb() const
{
  return this->damageNb_;
}

bool					Damage::canDamage() const
{
  return this->damageNb_ > 0;
}

void					Damage::applied()
{
  if (this->damageNb_ <= 0)
    return;
  if (al_get_time() - this->delayCounter_ < this->delay_)
    {
      this->delayCounter_ = al_get_time();
      return;
    }
  this->delayCounter_ = al_get_time();
  if (this->damageNb_ < 0)
    return;
  --this->damageNb_;
  if (this->damageNb_ <= 0)
    VISIBILITY(this->entity)->fadeOut(0.05, 30);
}