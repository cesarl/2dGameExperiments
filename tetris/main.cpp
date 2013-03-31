#include                                <allegro5/allegro.h>
#include				"SceneMenu.hh"
#include				"EventManager.hh"
#include				"SceneManager.hh"
#include				"ImageManager.hh"

static ALLEGRO_DISPLAY			*init(int width, int height)
{
  ALLEGRO_DISPLAY			*display;

  assert(al_init());
  assert(display = al_create_display(width, height));
  return display;
}

int					main()
{

  ALLEGRO_DISPLAY			*display = init(500, 400);
  SceneMenu				menu;
  SceneManager				sceneManager;
  EventManager				eventManager;

  sceneManager.add(&menu);
  menu.setActive(true);
  menu.setVisible(true);
  menu.setDisplay(display);
  eventManager.setSceneManager(&sceneManager);
  eventManager.play();
  al_destroy_display(display);
  return (1);
}
