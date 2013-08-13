#include				"GuiNumber.hh"

GuiNumber::GuiNumber(int val) :
  GuiComponent(),
  val_(val),
  font_(NULL)
{
  this->updateStr();
}

GuiNumber::~GuiNumber()
{}

void					GuiNumber::operator=(int val)
{
  this->val_ = val;
  this->updateStr();
  this->saveOptionValue();
}

void					GuiNumber::operator+=(int val)
{
  this->val_ += val;
  this->updateStr();
  this->saveOptionValue();
}

void					GuiNumber::operator-=(int val)
{
  this->val_ -= val;
  this->updateStr();
  this->saveOptionValue();
}

void					GuiNumber::operator*=(int val)
{
  this->val_ *= val;
  this->updateStr();
  this->saveOptionValue();
}

void					GuiNumber::operator/=(int val)
{
  this->val_ /= val;
  this->updateStr();
  this->saveOptionValue();
}

void					GuiNumber::setFont(ALLEGRO_FONT *font)
{
  this->font_ = font;
}

void					GuiNumber::draw(Vector3d *position)
{
  Vector3d				vec;

  vec = this->position_;
  if (position)
    vec += *position;
  if (!this->font_)
    return;
  al_draw_text(this->font_ , this->color_, vec.getX(), vec.getY(), 0, this->strVal_.c_str());
}

void					GuiNumber::updateStr()
{
  std::ostringstream			convert;

  convert << this->val_;
  this->strVal_ = convert.str();
}

int					GuiNumber::getVal() const
{
  return this->val_;
}

void					GuiNumber::saveOptionValue()
{
  if (!this->option_)
    return;
  static_cast<OptionValue<int>*>(this->option_)->setValue(this->val_);
}

void					GuiNumber::importOptionValue()
{
  OptionValue<int>			*value;

  if (!this->option_)
    return;
  value = dynamic_cast<OptionValue<int>*>(this->option_);
  if (!value)
    return;
  value->setValue(this->val_);
}
