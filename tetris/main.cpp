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
#include				"MainManager.hh"

int					main()
{
  if (!MainManager::getInstance()->initialize(50 * 20, 50 * 20))
    return -1;

  SceneMenu				menu;
  SceneMainGame				mainGame;
  ScenePause				pause;
  SceneGameOver				gameOver;
  SceneManager				*sceneManager;
  EventManager				*eventManager;

  FontManager::getInstance()->load("assets/fonts//LilitaOne-Regular.ttf", 80);
  FontManager::getInstance()->load("assets/fonts//LilitaOne-Regular.ttf", 50);
  ImageManager::getInstance()->load("assets/imgs/main-bg.jpg");
  ImageManager::getInstance()->load("assets/imgs/green_sky_background.jpg");
  ImageManager::getInstance()->load("assets/imgs/stars.png");
  SaveManager::getInstance()->load("saveFile.cfg");

  eventManager = EventManager::getInstance();
  sceneManager = SceneManager::getInstance();

  sceneManager->add(&menu);
  menu.setActive(true);
  menu.setVisible(true);
  menu.setName("menu");

  sceneManager->add(&mainGame);
  mainGame.setName("mainGame");

  sceneManager->add(&pause, HIGH);
  pause.setName("pause");

  sceneManager->add(&gameOver, HIGH);
  gameOver.setName("gameOver");

  sceneManager->initialize();

  eventManager->play();
  MainManager::getInstance()->deInitialize();
  return (1);
}
