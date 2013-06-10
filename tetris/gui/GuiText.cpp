#include				"GuiText.hh"

GuiText::GuiText(std::string const & val) :
  GuiComponent(),
  val_(val),
  font_(NULL)
{
}


GuiText::~GuiText()
{}

void					GuiText::operator=(std::string const & str)
{
  this->val_ = str;
  this->saveOptionValue();
}

void					GuiText::operator+=(std::string const & str)
{
  this->val_ += str;
  this->saveOptionValue();
}

void					GuiText::setFont(ALLEGRO_FONT *font)
{
  this->font_ = font;
}

void					GuiText::draw(Vector3d *position)
{
  Vector3d				vec;

  vec = this->position_;
  if (position)
    vec += *position;
  if (!this->font_)
    return;
  al_draw_text(this->font_ , this->color_, vec.getX(), vec.getY(), 0, this->val_.c_str());
}

void					GuiText::saveOptionValue()
{
  if (!this->option_)
    return;
  static_cast<OptionValue<std::string>*>(this->option_)->setValue(this->val_);
}

void					GuiText::importOptionValue()
{
  OptionValue<std::string>		*value;

  if (!this->option_)
    return;
  value = dynamic_cast<OptionValue<std::string>*>(this->option_);
  if (!value)
    return;
  value->setValue(this->val_);
}

