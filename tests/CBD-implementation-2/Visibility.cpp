#include				"Visibility.hh"
#include				"ComponentTypes.hh"

#include				<iostream> //pour le debug - a virer

Visibility::Visibility(Entity *entity) : AComponent(entity, T_VISIBILITY, 1)
{
  this->visible = true;
  this->opacity = 255;
  this->timeCounter_ = -1;
  this->fade_ = 0;
  this->speed_ = 0;
}

Visibility::~Visibility()
{}

void					Visibility::update(double time)
{
  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;
  if (this->fade_ == 0)
    return;
  if (this->timeCounter_ == -1)
    this->timeCounter_ = time;
  if (time - this->timeCounter_ < this->speed_)
    return;
  this->opacity += this->fade_;
  if (this->opacity <= 0)
    {
      this->visible = false;
      this->fade_ = 0;
      this->opacity = 0;
    }
  else if (this->opacity > 255)
    {
      this->fade_ = 0;
      this->opacity = 255;
    }
  else
    this->visible = true;
  this->timeCounter_ = time;
}

void					Visibility::draw()
{}

void					Visibility::fadeOut(double speed, unsigned int ratio)
{
  this->speed_ = speed;
  this->fade_ = -1 * ratio;
}

void					Visibility::fadeIn(double speed, unsigned int ratio)
{
  this->speed_ = speed;
  this->fade_ = ratio;
}

void					Visibility::setVisible(bool value)
{
  this->visible = value;
}
