#include				"Logger.hpp"
#include				"ImageLoader.hpp"
#include				"SkyboxLoader.hpp"
#include				"MediaManager.hpp"
#include				"ResourceManager.hpp"
#include				"MainManager.hpp"
#include				"Camera.hpp"
#include				<exception>

#include				"EntityManager.hpp"

static Camera<Orthographic, FlatCamera> camera;

void					draw(float time, const ALLEGRO_EVENT &ev)
{
  static ImagePtr img = ResourceManager::getInstance().get<Image>("stars.png");

  camera.update(time, ev);
  img->draw3d();

  (void)ev;
  (void)time;
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


  unsigned int firstEntity = EntityManager::getInstance().newEntity();
  ILogger::log("Ma premiere entite c'est %i !", firstEntity);

  unsigned int secondEntity = EntityManager::getInstance().newEntity();
  ILogger::log("Ma deuxieme entite c'est %i !", secondEntity);

  EntityManager::getInstance().eraseEntity(firstEntity);

  unsigned int thirdEntity = EntityManager::getInstance().newEntity();
  ILogger::log("Ma troisieme entite c'est %i !", thirdEntity);


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
