#include				"Logger.hpp"
#include				"ImageLoader.hpp"
#include				"SkyboxLoader.hpp"
#include				"MediaManager.hpp"
#include				"ResourceManager.hpp"
#include				"MainManager.hpp"
#include				"Camera.hpp"
#include				<exception>

#include				"EntityManager.hpp"
#include				"ComponentManager.hpp"
#include				"SystemManager.hpp"
#include				"ImageSystem.hpp"
#include				"VelocitySystem.hpp"
#include				"MapGenerator.hpp"

#include				"Components.hpp"

static Camera<Orthographic, FlatCamera> camera;

void					draw(float time, const ALLEGRO_EVENT &ev)
{
  static double				fps = 0;
  static int				frames_done = 0;
  static double				old_time = al_get_time();

  camera.update(time, ev);
  EntityManager::getInstance().update(time, ev);

  if(time - old_time >= 1.0)
    {
      fps = frames_done / (time - old_time);
      frames_done = 0;
      old_time = time;
      std::cout << fps << std::endl;
    }
  frames_done++;
}

void					key(float time, const ALLEGRO_EVENT &ev)
{
  camera.input(time, ev);
  (void)time;
}

int					main()
{

  ////////////////////
  // initialisation //
  ////////////////////

  if (!MainManager::getInstance().init())
    return 0;
  if (!MainManager::getInstance().launch(1000, 800))
    return 0;

  //////////
  // main //
  //////////

  MediaManager::getInstance().registerLoader(new ImageLoader, ".jpg,.png,.jpeg");
  MediaManager::getInstance().registerLoader(new SkyboxLoader, ".skybox");
  MediaManager::getInstance().addSearchPath("./assets/imgs/");

  // ILogger::log("Il y a %i instances de la meme image stars.png", img->getCounter());

  EventManager::getInstance().setDrawLoop(draw);
  EventManager::getInstance().setKeyLoop(key);

  if (!camera.init())
    return 0;

  SystemManager::getInstance().add<ImageSystem>(10);
  SystemManager::getInstance().add<VelocitySystem>(1);

  MapGenerator g;
  g.generate(33, 33);


  try
    {
      EventManager::getInstance().play();
    }
  catch (const std::exception &e)
    {
      ILogger::log(e.what());
    }
  return 0;
}
