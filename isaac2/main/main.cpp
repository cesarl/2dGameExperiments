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
#include				"BoundingBoxSystem.hpp"
#include				"RotationForceSystem.hpp"
#include				"InputMovementSystem.hpp"
#include				"VelocityFrictionSystem.hpp"
#include				"PhysicSystem.hpp"

#include				"MapGenerator.hpp"

#include				"Components.hpp"

static Camera<Orthographic, FlatCamera> camera;
// static Camera<Perspective, FreeFly> camera;

void					draw(float time, const ALLEGRO_EVENT &ev)
{
  static double				fps = 0;
  static int				frames_done = 0;
  static double				old_time = al_get_time();

  camera.update(time, ev);
  SystemManager::getInstance().update(time, ev);

  if(time - old_time >= 1.0)
    {
      fps = frames_done / (time - old_time);
      frames_done = 0;
      old_time = time;
      std::cout << fps << std::endl;
    }
  frames_done++;

  static MapGenerator g;
if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_G)
    g.generate(21, 11);


}

void					key(float time, const ALLEGRO_EVENT &ev)
{
  camera.input(time, ev);

  static MapGenerator g;
  if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
    g.generate(21, 11);

  (void)time;
}

int					main()
{

  ////////////////////
  // initialisation //
  ////////////////////

  if (!MainManager::getInstance().init())
    return 0;
  if (!MainManager::getInstance().launch(1344, 704))
    return 0;

  //////////
  // main //
  //////////

  MediaManager::getInstance().registerLoader(new ImageLoader, ".jpg,.png,.jpeg");
  MediaManager::getInstance().registerLoader(new SkyboxLoader, ".skybox");
  MediaManager::getInstance().addSearchPath("./assets/imgs/");

  EventManager::getInstance().setDrawLoop(draw);
  EventManager::getInstance().setKeyLoop(key);

  if (!camera.init())
    return 0;

  SystemManager::getInstance().add<ImageSystem>(10);
  SystemManager::getInstance().add<VelocitySystem>(9);
  SystemManager::getInstance().add<BoundingBoxSystem>(3);
  SystemManager::getInstance().add<InputMovementSystem>(1);
  SystemManager::getInstance().add<RotationForceSystem>(3);
  SystemManager::getInstance().add<VelocityFrictionSystem>(2);
  SystemManager::getInstance().add<PhysicSystem>(4);


  ////////////////////
  // GENRATE PLAYER //
  ////////////////////

  unsigned int				e;

  EntityManager::getInstance().newEntity();
  e = EntityManager::getInstance().newEntity();
  ComponentManager::getInstance().addComponent<Rotation>(e);
  Position &posC = ComponentManager::getInstance().addComponent<Position>(e);
  Img &imgC = ComponentManager::getInstance().addComponent<Img>(e);
  Scale &scaleC = ComponentManager::getInstance().addComponent<Scale>(e);
  Color &colorC = ComponentManager::getInstance().addComponent<Color>(e);
  BoundingBox &bbC = ComponentManager::getInstance().addComponent<BoundingBox>(e);
  Physic &phy = ComponentManager::getInstance().addComponent<Physic>(e);
  ComponentManager::getInstance().addComponent<InputMovement>(e).speed = 7.0f;
  ComponentManager::getInstance().addComponent<VelocityFriction>(e).friction = 0.999f;
  ComponentManager::getInstance().addComponent<Velocity>(e);

  colorC.set(0.0f, 1.0f, 1.0f, 1.0f);
  bbC.set(Vector3d(50.0f, 45.0f, 0.0f));
  posC.position = Vector3d(64.0f * 2.0f, 64.0f * 2.0f, 100.0f);
  imgC.img = ResourceManager::getInstance().get<Image>("kitty.jpg");
  scaleC.scale = Vector3d(50.0f, 45.0f, 0.0f);
  phy.fixed = false;


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
