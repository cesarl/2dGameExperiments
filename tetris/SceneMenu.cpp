#include				"SceneMenu.hh"

SceneMenu::SceneMenu()
{}

SceneMenu::~SceneMenu()
{}

void					SceneMenu::update(ALLEGRO_EVENT *event)
{
  // std::cout << "update" << std::endl;
  (void)(event);
}

void					SceneMenu::draw(ALLEGRO_EVENT *event)
{
  (void)(event);
}

void					SceneMenu::input(ALLEGRO_EVENT *event)
{
  std::cout << "input" << std::endl;
  (void)(event);
}
