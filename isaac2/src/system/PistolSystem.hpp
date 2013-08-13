#ifndef				__PISTOL_SYSTEM_HPP__
# define			__PISTOL_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

class				PistolSystem : public System
{
public:
  virtual ~PistolSystem()
  {}

  PistolSystem()
  {}

  void				init()
  {
    require<Pistol>();
    require<Position>();
  }


  unsigned int			createBullet(const Vector3d & position, const Vector3d & dir, unsigned int entity)
  {
    unsigned int		e;
    static ComponentManager	&c = ComponentManager::getInstance();

    e = EntityManager::getInstance().newEntity();
    EntityManager::getInstance().getEntityData(e).setLayer("Good");

    Position &posComponent = c.addComponent<Position>(e);
    Img &imgComponent = c.addComponent<Img>(e);
    Scale &scaleComponent = c.addComponent<Scale>(e);
    Color &colorComponent = c.addComponent<Color>(e);
    RotationForce &rotForce = c.addComponent<RotationForce>(e);
    Velocity &vel = c.addComponent<Velocity>(e);
    Rotation &rot = c.addComponent<Rotation>(e);
    BoundingBox &bbComponent = c.addComponent<BoundingBox>(e);
    Physic &phy = c.addComponent<Physic>(e);
    Lifetime &life = c.addComponent<Lifetime>(e);

    c.addComponent<VelocityFriction>(e).friction = 0.9999f;
    bbComponent.set(Vector3d(32.0f, 32.0f, 0.0f));
    phy.fixed = false;
    vel.velocity = dir;
    vel.velocity *= 700.0f;
    vel.velocity += c.getComponent<Velocity>(entity)->velocity;
    posComponent.position = position;
    posComponent.position.z = 1000;
    imgComponent.img = ResourceManager::getInstance().get<Image>("stars.png");
    scaleComponent.scale = Vector3d(32.0f, 32.0f, 0.0f);
    rotForce.force = Vector3d(0.0f, 0.0f, 25.0f);
    colorComponent = (Color(1.0f, 0.0f, 1.0f, 1.0f));
    life.time = 3.0f;

    (void)rot;
    return e;
  }

  virtual void			update(unsigned int entity, float time, const ALLEGRO_EVENT &)
  {
    Pistol			*pistol = ComponentManager::getInstance().getComponent<Pistol>(entity);
    static InputSystem		*sys = SystemManager::getInstance().getSystem<InputSystem>();
 
    if (!pistol)
      return;

    if (pistol->fireRateCache > 0.0f)
      {
	pistol->fireRateCache -= time;
	return;
      }

    unsigned int b = 0;
    Vector3d dir;
    Position			*position = ComponentManager::getInstance().getComponent<Position>(entity);

    if (sys->isDown(ALLEGRO_KEY_LEFT)
	&& sys->isDown(ALLEGRO_KEY_UP)) // left up
      {
	b = createBullet(position->position, Vector3d(-1, 1, 0), entity);
      }
    else if (sys->isDown(ALLEGRO_KEY_LEFT)
	     && sys->isDown(ALLEGRO_KEY_DOWN)) // left down
      {
	b = createBullet(position->position, Vector3d(-1, -1, 0), entity);
      }
    else if (sys->isDown(ALLEGRO_KEY_RIGHT)
	     && sys->isDown(ALLEGRO_KEY_UP)) // right up
      {
	b = createBullet(position->position, Vector3d(1, 1, 0), entity);
      }
    else if (sys->isDown(ALLEGRO_KEY_RIGHT)
	     && sys->isDown(ALLEGRO_KEY_DOWN)) // right down
      {
	b = createBullet(position->position, Vector3d(1, -1, 0), entity);
      }
    else if (sys->isDown(ALLEGRO_KEY_LEFT)) // left
      {
	b = createBullet(position->position, Vector3d(-1, 0, 0), entity);
      }
    else if (sys->isDown(ALLEGRO_KEY_RIGHT)) // right
      {
	b = createBullet(position->position, Vector3d(1, 0, 0), entity);
      }
    else if (sys->isDown(ALLEGRO_KEY_UP)) // up
      {
	b = createBullet(position->position, Vector3d(0, 1, 0), entity);
      }
    else if (sys->isDown(ALLEGRO_KEY_DOWN)) // down
      {
	b = createBullet(position->position, Vector3d(0, -1, 0), entity);
      }

    if (b == 0)
      return;

    if (pistol->fireRateCache <= 0.0f)
      {
	pistol->fireRateCache = pistol->fireRate;
      }

    // std::cout << "New bullet : " << b << std::endl;
    (void)b;
  }
private:
};

#endif				// __PISTOL_SYSTEM_HPP__
