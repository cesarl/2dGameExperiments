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

  ALLEGRO_DISPLAY			*display = init(749, 1080);
  SceneMenu				menu;
  SceneManager				sceneManager;
  EventManager				eventManager;

  FontManager::getInstance()->load("assets/fonts//LilitaOne-Regular.ttf", 80);
  FontManager::getInstance()->load("assets/fonts//LilitaOne-Regular.ttf", 50);
  ImageManager::getInstance()->load("assets/imgs/blue_sky_background.jpg");

  sceneManager.add(&menu);
  menu.setActive(true);
  menu.setVisible(true);
  menu.setDisplay(display);
  eventManager.setSceneManager(&sceneManager);
  eventManager.play();
  al_destroy_display(display);
  return (1);
}
