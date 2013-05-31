#include				"SceneMenu.hh"

SceneMenu::SceneMenu()
{}

SceneMenu::~SceneMenu()
{}

bool					SceneMenu::initialize()
{
  EntityManager::getInstance()->pushGenerationRule(gnRoom);
  EntityManager::getInstance()->pushGenerationRule(gnPnj);
  EntityManager::getInstance()->pushGenerationRule(gnHeros);
  if (!EntityManager::getInstance()->generate(-1))
    return false;
  return true;
}

void					SceneMenu::uninitialize()
{}


void					SceneMenu::update(ALLEGRO_EVENT *event)
{
  EntityManager::getInstance()->update();
  (void)(event);
}

void					SceneMenu::draw(ALLEGRO_EVENT *event)
{
  EntityManager::getInstance()->draw();
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
