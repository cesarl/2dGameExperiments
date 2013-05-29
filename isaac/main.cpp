#include                                <allegro5/allegro.h>
#include				"SceneMenu.hh"
#include				"EventManager.hh"
#include				"SceneManager.hh"
#include				"MainManager.hh"

int					main()
{
  if (!MainManager::getInstance()->initialize(64 * 20, 64 * 10))
    return -1;

  SceneMenu				menu;
  SceneManager				*sceneManager;
  EventManager				*eventManager;

  eventManager = EventManager::getInstance();
  sceneManager = SceneManager::getInstance();

  sceneManager->add(&menu);
  menu.setActive(true);
  menu.setVisible(true);
  menu.setName("menu");

  sceneManager->initialize();
  eventManager->play();

  MainManager::getInstance()->deInitialize();
  return (1);
}
