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

  for (int i = 0; i < 1000; ++i)
    {
      unsigned int				thirdEntity;

      thirdEntity = EntityManager::getInstance().newEntity();
      // ILogger::log("Ma troisieme entite c'est %i !", thirdEntity);
      Position &posComponent = ComponentManager::getInstance().addComponent<Position>(thirdEntity);
      Img &imgComponent = ComponentManager::getInstance().addComponent<Img>(thirdEntity);
      Velocity &velComponent = ComponentManager::getInstance().addComponent<Velocity>(thirdEntity);
      ComponentManager::getInstance().addComponent<Color>(thirdEntity);
      Scale &scaleComponent = ComponentManager::getInstance().addComponent<Scale>(thirdEntity);
      Rotation &rotationComponent = ComponentManager::getInstance().addComponent<Rotation>(thirdEntity);

      posComponent.position = Vector3d(rand() % 900, rand() % 700, rand() % 400);
      imgComponent.img = ResourceManager::getInstance().get<Image>("stars.png");
      velComponent.velocity = Vector3d(float(rand() % 2 - 1) / 10.0f,
				       float(rand() % 2 - 1) / 10.0f,
				       float(rand() % 2 - 1) / 10.0f);
      scaleComponent.scale = Vector3d(rand() % 200, rand() % 200, rand() % 200);
      rotationComponent.rotation = Vector3d(rand() % 360, rand() % 360, rand() % 360);
    }

  SystemManager::getInstance().add<ImageSystem>(10);
  SystemManager::getInstance().add<VelocitySystem>(1);

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
