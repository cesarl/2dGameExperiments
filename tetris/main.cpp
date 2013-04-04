#include                                <allegro5/allegro.h>
#include				"SceneMenu.hh"
#include				"SceneMainGame.hh"
#include				"ScenePause.hh"
#include				"SceneGameOver.hh"
#include				"EventManager.hh"
#include				"SceneManager.hh"
#include				"ImageManager.hh"
#include				"SaveManager.hh"
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
  ALLEGRO_DISPLAY			*display = init(50 * 20, 50 * 20);
  SceneMenu				menu;
  SceneMainGame				mainGame;
  ScenePause				pause;
  SceneGameOver				gameOver;
  SceneManager				sceneManager;
  EventManager				eventManager;

  FontManager::getInstance()->load("assets/fonts//LilitaOne-Regular.ttf", 80);
  FontManager::getInstance()->load("assets/fonts//LilitaOne-Regular.ttf", 50);
  ImageManager::getInstance()->load("assets/imgs/main-bg.jpg");
  ImageManager::getInstance()->load("assets/imgs/green_sky_background.jpg");
  SaveManager::getInstance()->load("saveFile.cfg");

  sceneManager.add(&menu);
  menu.setActive(true);
  menu.setVisible(true);
  menu.setDisplay(display);
  menu.setName("menu");

  sceneManager.add(&mainGame);
  mainGame.setDisplay(display);
  mainGame.setName("mainGame");

  sceneManager.add(&pause, HIGH);
  pause.setDisplay(display);
  pause.setName("pause");

  sceneManager.add(&gameOver, HIGH);
  gameOver.setDisplay(display);
  gameOver.setName("gameOver");

  eventManager.setSceneManager(&sceneManager);
  eventManager.play();
  al_destroy_display(display);
  return (1);
}
