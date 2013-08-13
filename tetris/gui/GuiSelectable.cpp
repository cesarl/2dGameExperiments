#include				"GuiSelectable.hh"

GuiSelectable::GuiSelectable() :
  GuiComponent(),
  selected_(false),
  pressAction_(NULL),
  selectAction_(NULL),
  unselectAction_(NULL),
  deleteAction_(NULL)
{
  this->selectable_ = true;
}

GuiSelectable::~GuiSelectable()
{}

void					GuiSelectable::select(bool val)
{
  this->selected_ = val;
  if (val && this->selectAction_)
    {
      this->selectAction_(this);
    }
  if (!val && this->unselectAction_)
    {
      this->unselectAction_(this);
    }
}

void					GuiSelectable::pressed()
{
  if (this->pressAction_)
    {
      this->pressAction_(this);
    }
}

void					GuiSelectable::setPressAction(void (* function)(GuiComponent *gui))
{
  this->pressAction_ = function;
}

void					GuiSelectable::setSelectAction(void (* function)(GuiComponent *gui))
{
  this->selectAction_ = function;
}

void					GuiSelectable::setUnselectAction(void (* function)(GuiComponent *gui))
{
  this->unselectAction_ = function;
}

void					GuiSelectable::setDeleteAction(void (* function)(GuiComponent *gui))
{
  this->deleteAction_ = function;
}

void					GuiSelectable::event(ALLEGRO_EVENT *event)
{
  if (event->type != ALLEGRO_EVENT_KEY_DOWN)
    return;
  switch (event->keyboard.keycode)
    {
    case ALLEGRO_KEY_ENTER:
      this->pressed();
      break;
    }
}
