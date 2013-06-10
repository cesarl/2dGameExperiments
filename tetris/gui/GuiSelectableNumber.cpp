#include				"GuiSelectableNumber.hh"

GuiSelectableNumber::GuiSelectableNumber() :
  GuiSelectable()
{}

GuiSelectableNumber::~GuiSelectableNumber()
{}

void					GuiSelectableNumber::setupNumber(int val, ALLEGRO_FONT *font)
{
  this->nbr_ = val;
  this->nbr_.setFont(font);
}

GuiNumber				*GuiSelectableNumber::getNumber()
{
  return &(this->nbr_);
}

int					GuiSelectableNumber::getVal() const
{
  return this->nbr_.getVal();
}

void					GuiSelectableNumber::draw(Vector3d *position)
{
  Vector3d				vec;

  vec = this->position_;
  if (position)
    vec += *position;
  this->nbr_.draw(&vec);
}

void					GuiSelectableNumber::attachOption(Option *option)
{
  this->nbr_.attachOption(option);
}

void					GuiSelectableNumber::select(bool val)
{
  this->selected_ = val;
  if (val && this->selectAction_)
    {
      this->selectAction_(this);
      this->nbr_.saveOptionValue();
    }
  if (!val && this->unselectAction_)
    {
      this->unselectAction_(this);
    }
}

void					GuiSelectableNumber::setColor(ALLEGRO_COLOR color)
{
  this->nbr_.setColor(color);
}
