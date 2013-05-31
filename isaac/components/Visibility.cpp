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
  this->blinkNb_ = 0;
}

Visibility::~Visibility()
{}

void					Visibility::update(double time)
{
  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;

  if (this->fade_ != 0)
    {
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
    }
  if (this->blinkNb_ > 0)
    {
      if (this->blinkTimeCounter_ == 0 || time - this->blinkTimeCounter_ >= this->blinkSpeed_)
	{
	  this->opacity = this->opacity == 0 ? 255 : 0;
	  this->blinkTimeCounter_ = time;
	  ++this->blinkCounter_;
	}
      if (this->blinkCounter_ >= this->blinkNb_)
	{
	  this->blinkNb_ = 0;
	  this->opacity = 255;
	}
    }
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

void					Visibility::blink(int nb, double speed)
{
  this->blinkCounter_ = 0;
  this->blinkNb_ = nb;
  this->blinkSpeed_ = speed;
  this->blinkTimeCounter_ = 0;
}

void					Visibility::serialize(std::ofstream *file)
{
  int					type = T_VISIBILITY;

  file->write(reinterpret_cast<const char *>(&type), sizeof(type));
  file->write(reinterpret_cast<const char *>(&this->timeCounter_), sizeof(double));
  file->write(reinterpret_cast<const char *>(&this->fade_), sizeof(int));
  file->write(reinterpret_cast<const char *>(&this->speed_), sizeof(double));
  file->write(reinterpret_cast<const char *>(&this->blinkSpeed_), sizeof(double));
 file->write(reinterpret_cast<const char *>(&this->blinkNb_), sizeof(int));
 file->write(reinterpret_cast<const char *>(&this->blinkCounter_), sizeof(int));
 file->write(reinterpret_cast<const char *>(&this->blinkTimeCounter_), sizeof(int));
}

void					Visibility::unserialize(std::ifstream *file)
{
  file->read(reinterpret_cast<char *>(&this->timeCounter_), sizeof(double));
  file->read(reinterpret_cast<char *>(&this->fade_), sizeof(int));
  file->read(reinterpret_cast<char *>(&this->speed_), sizeof(double));
  file->read(reinterpret_cast<char *>(&this->blinkSpeed_), sizeof(double));
 file->read(reinterpret_cast<char *>(&this->blinkNb_), sizeof(int));
 file->read(reinterpret_cast<char *>(&this->blinkCounter_), sizeof(int));
 file->read(reinterpret_cast<char *>(&this->blinkTimeCounter_), sizeof(int));
}
