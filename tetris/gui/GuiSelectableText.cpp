#include				"GuiSelectableText.hh"

GuiSelectableText::GuiSelectableText() :
  GuiSelectable()
{}

GuiSelectableText::~GuiSelectableText()
{}

void					GuiSelectableText::setupText(std::string const & val, ALLEGRO_FONT *font)
{
  this->text_ = val;
  this->text_.setFont(font);
}

GuiText					*GuiSelectableText::getText()
{
  return &(this->text_);
}

void					GuiSelectableText::draw(Vector3d *position)
{
  Vector3d				vec;

  vec = this->position_;
  if (position)
    vec += *position;
  this->text_.draw(&vec);
}

void					GuiSelectableText::attachOption(Option *option)
{
  this->text_.attachOption(option);
}

void					GuiSelectableText::select(bool val)
{
  this->selected_ = val;
  if (val && this->selectAction_)
    {
      this->selectAction_(this);
      this->text_.saveOptionValue();
    }
  if (!val && this->unselectAction_)
    {
      this->unselectAction_(this);
    }
}

void					GuiSelectableText::setColor(ALLEGRO_COLOR color)
{
  this->text_.setColor(color);
}

