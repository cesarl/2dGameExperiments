#include				"SceneMenu.hh"

SceneMenu::SceneMenu()
{
  this->room_.generate();
}

SceneMenu::~SceneMenu()
{}

void					SceneMenu::update(ALLEGRO_EVENT *event)
{
  this->room_.update(event);
  (void)(event);
}

void					SceneMenu::draw(ALLEGRO_EVENT *event)
{
  this->room_.draw(event);
  (void)(event);
}

void					SceneMenu::input(ALLEGRO_EVENT *event)
{
  (void)(event);
}

void					SceneMenu::receiveMessage(e_message type, bool activate)
{
  (void)type;
  (void)activate;
}

void					SceneMenu::receiveMessage(e_message type, void *data)
{
  (void)type;
  (void)data;
}
