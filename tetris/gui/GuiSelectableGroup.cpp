#include				"GuiSelectableGroup.hh"

GuiSelectableGroup::GuiSelectableGroup() :
  GuiSelectable(),
  horizontal_(false)
{}

GuiSelectableGroup::~GuiSelectableGroup()
{}

void					GuiSelectableGroup::clear()
{
  t_iter				it;

  it = this->sellist_.begin();
  while (it != this->sellist_.end())
    {
      delete *it;
      ++it;
    }
  this->sellist_.clear();
  this->selected_ = this->sellist_.end();
  it = this->list_.begin();
  while (it != this->list_.end())
    {
      delete *it;
      ++it;
    }
  this->list_.clear();
}

void					GuiSelectableGroup::pushComponent(GuiComponent *component)
{
  if (component->isSelectable())
    this->sellist_.push_back(component);
  else
    this->list_.push_back(component);
  component->setParent(this);
  this->selectFirst();
  if (this->selected_ != this->sellist_.end())
    (*this->selected_)->select(true);
  if (component->isSelectable() && this->option_)
    component->attachOption(this->option_);
}

void					GuiSelectableGroup::draw(Vector3d *position)
{
  Vector3d				vec;
  t_iter				it;

  vec = this->position_;
  if (position)
    vec += *position;
  if (this->list_.size() > 0)
    {
      it = this->list_.begin();
      while (it != this->list_.end())
	{
	  (*it)->draw(&vec);
	  ++it;
	}
    }
  if (this->sellist_.size() > 0)
    {
      it = this->sellist_.begin();
      while (it != this->sellist_.end())
	{
	  (*it)->draw(&vec);
	  ++it;
	}
    }
}

void					GuiSelectableGroup::setHorizontal(bool val)
{
  this->horizontal_ = val;
}

void					GuiSelectableGroup::event(ALLEGRO_EVENT *event)
{
  t_iter				it;

  if (this->selected_ != this->sellist_.end()
      && (*this->selected_)->isSelectable())
    (*this->selected_)->event(event);
  if (event->type != ALLEGRO_EVENT_KEY_DOWN)
    return;
  switch (event->keyboard.keycode)
    {
    case ALLEGRO_KEY_UP:
      if (this->horizontal_)
	break;
      this->selectPrev();
      break;
    case ALLEGRO_KEY_DOWN:
      if (this->horizontal_)
	break;
      this->selectNext();
      break;
    case ALLEGRO_KEY_LEFT:
      if (!this->horizontal_)
	break;
      this->selectPrev();
      break;
    case ALLEGRO_KEY_RIGHT:
      if (!this->horizontal_)
	break;
      this->selectNext();
      break;
    case ALLEGRO_KEY_ENTER:
      this->pressed();
      break;
    case ALLEGRO_KEY_BACKSPACE:
      if (this->deleteAction_)
	this->deleteAction_(this);
      break;
    }
}

void					GuiSelectableGroup::selectNext()
{
  if (this->sellist_.size() == 0)
    {
      this->selected_ = this->sellist_.end();
      return;
    }
  if (this->selected_ != this->sellist_.end())
    (*this->selected_)->select(false);
  ++this->selected_;
  if (this->selected_ == this->sellist_.end())
    this->selected_ = this->sellist_.begin();
  (*this->selected_)->select(true);
}

void					GuiSelectableGroup::selectPrev()
{
  if (this->sellist_.size() == 0)
    {
      this->selected_ = this->sellist_.end();
      return;
    }
  if (this->selected_ != this->sellist_.end())
    (*this->selected_)->select(false);
  if (this->selected_ == this->sellist_.begin())
    {
      this->selected_ = this->sellist_.end();
      --this->selected_;
    }
  else
    --this->selected_;
  (*this->selected_)->select(true);
}

void					GuiSelectableGroup::selectFirst()
{
  if (this->sellist_.size() == 0)
    {
      this->selected_ = this->sellist_.end();
      return;
    }
  this->selected_ = this->sellist_.begin();
  while (this->selected_ != this->sellist_.end() && !(*this->selected_)->isSelectable())
    ++this->selected_;
}

void					GuiSelectableGroup::setColor(ALLEGRO_COLOR color)
{
  t_iter				it;

  if (this->list_.size() > 0)
    {
      it = this->list_.begin();
      while (it != this->list_.end())
	{
	  (*it)->setColor(color);
	  ++it;
	}
    }
  if (this->sellist_.size() > 0)
    {
      it = this->sellist_.begin();
      while (it != this->sellist_.end())
	{
	  (*it)->setColor(color);
	  ++it;
	}
    }
}
