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

static Camera<Orthographic, FlatCamera> camera;
unsigned int				thirdEntity;

void					draw(float time, const ALLEGRO_EVENT &ev)
{
  static double				fps = 0;
  static int				frames_done = 0;
  static double				old_time = al_get_time();

  camera.update(time, ev);
  EntityManager::getInstance().update(time, ev);
  ComponentManager::getInstance().getComponent<Img>(thirdEntity)->img = ResourceManager::getInstance().get<Image>("stars.png");


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

  ILogger::log("Le type de EventManager c'est %i !", ComponentTypeManager::getInstance().getComponentType<EventManager>());

  ILogger::log("Le type de SystemManager c'est %i !", ComponentTypeManager::getInstance().getComponentType<SystemManager>());

  ILogger::log("Le type de EventManager c'est %i !", ComponentTypeManager::getInstance().getComponentType<EventManager>());

  // unsigned int firstEntity = EntityManager::getInstance().newEntity();
  // ILogger::log("Ma premiere entite c'est %i !", firstEntity);

  // unsigned int secondEntity = EntityManager::getInstance().newEntity();
  // ILogger::log("Ma deuxieme entite c'est %i !", secondEntity);

  // EntityManager::getInstance().eraseEntity(firstEntity);

  thirdEntity = EntityManager::getInstance().newEntity();
  ILogger::log("Ma troisieme entite c'est %i !", thirdEntity);


  Position &posComponent = ComponentManager::getInstance().addComponent<Position>(thirdEntity);
  Img &imgComponent = ComponentManager::getInstance().addComponent<Img>(thirdEntity);
  Velocity &velComponent = ComponentManager::getInstance().addComponent<Velocity>(thirdEntity);

  posComponent.position = Vector3d(1.0f, 1.0f, 0.0f);
  imgComponent.img = ResourceManager::getInstance().get<Image>("stars.png");
  velComponent.velocity = Vector3d(0.001f, 0.001f, 0.0f);

  //  ComponentManager::getInstance().removeComponent<Position>(thirdEntity);

  ImageSystem *imgSys = new ImageSystem();
  VelocitySystem *velSys = new VelocitySystem();

  imgSys->require<Img>();
  imgSys->require<Position>();

  velSys->require<Position>();
  velSys->require<Velocity>();

  SystemManager::getInstance().add(imgSys);
  SystemManager::getInstance().add(velSys);

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
