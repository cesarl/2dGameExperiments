#include				"GuiRangeNumber.hh"

GuiRangeNumber::GuiRangeNumber() :
  GuiSelectableNumber(),
  min_(-2147483648),
  max_(2147483647)
{}

GuiRangeNumber::~GuiRangeNumber()
{}

void					GuiRangeNumber::setBounds(int min, int max)
{
  this->min_ = min;
  this->max_ = max;
  if (this->nbr_.getVal() < this->min_)
    this->nbr_ = this->min_;
  else if (this->nbr_.getVal() > this->max_)
    this->nbr_ = this->max_;
  this->nbr_.updateStr();
}

void					GuiRangeNumber::event(ALLEGRO_EVENT *event)
{
  if (event->type != ALLEGRO_EVENT_KEY_DOWN)
    return;
  switch (event->keyboard.keycode)
    {
    case ALLEGRO_KEY_LEFT:
      this->increment(-1);
      break;
    case ALLEGRO_KEY_RIGHT:
      this->increment(1);
      break;
    }
}

void					GuiRangeNumber::increment(int n)
{
  this->nbr_ += n;
  if (this->nbr_.getVal() < this->min_)
    this->nbr_ = this->min_;
  else if (this->nbr_.getVal() > this->max_)
    this->nbr_ = this->max_;
  this->nbr_.updateStr();
}
