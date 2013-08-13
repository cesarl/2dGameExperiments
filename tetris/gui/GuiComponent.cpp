#include				"GuiComponent.hh"


GuiComponent::GuiComponent() :
  visible_(true),
  parent_(NULL),
  selectable_(false),
  option_(NULL),
  color_(al_map_rgb(150, 150, 150))
{}

GuiComponent::~GuiComponent()
{}

void					GuiComponent::setPosition(Vector3d const & pos)
{
  this->position_ = pos;
}

void					GuiComponent::setVisible(bool val)
{
  this->visible_ = val;
}

void					GuiComponent::draw(Vector3d *position)
{
  (void)(position);
}

void					GuiComponent::event(ALLEGRO_EVENT *event)
{
  (void)(event);
}

Vector3d				&GuiComponent::getPosition()
{
  return this->position_;
}

void					GuiComponent::setParent(GuiComponent *parent)
{
  this->parent_ = parent;
}

GuiComponent				*GuiComponent::getParent() const
{
  return this->parent_;
}

bool					GuiComponent::isSelectable() const
{
  return this->selectable_;
}

void					GuiComponent::select(bool val)
{
  (void)(val);
}

void					GuiComponent::attachOption(Option *option)
{
  this->option_ = option;
}

void					GuiComponent::saveOptionValue()
{}

void					GuiComponent::importOptionValue()
{}

void					GuiComponent::setColor(ALLEGRO_COLOR color)
{
  this->color_ = color;
}

void					GuiComponent::setId(int id)
{
  this->id_ = id;
}

int					GuiComponent::getId() const
{
  return this->id_;
}
