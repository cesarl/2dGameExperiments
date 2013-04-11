#include                                <allegro5/allegro.h>
#include				"SceneMenu.hh"
#include				"EventManager.hh"
#include				"SceneManager.hh"
#include				"ImageManager.hh"
#include				"FontManager.hh"

static ALLEGRO_DISPLAY			*init(int width, int height)
{
  ALLEGRO_DISPLAY			*display;

  assert(al_init());
  assert(display = al_create_display(width, height));
  return display;
}

int					main()
{
  ALLEGRO_DISPLAY			*display = init(64 * 20, 64 * 10);
  SceneMenu				menu;
  SceneManager				sceneManager;
  EventManager				*eventManager;

  eventManager = EventManager::getInstance();

  sceneManager.add(&menu);
  menu.setActive(true);
  menu.setVisible(true);
  menu.setDisplay(display);
  menu.setName("menu");

  eventManager->setSceneManager(&sceneManager);
  eventManager->play();
  al_destroy_display(display);
  return (1);
}
