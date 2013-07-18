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


  unsigned int			createBullet(const Vector3d & position)
  {
    unsigned int		e;
    ComponentManager		&c = ComponentManager::getInstance();

    e = EntityManager::getInstance().newEntity();
    Position &posComponent = c.addComponent<Position>(e);
    Img &imgComponent = c.addComponent<Img>(e);
    Scale &scaleComponent = c.addComponent<Scale>(e);
    Color &colorComponent = c.addComponent<Color>(e);
    RotationForce &rotForce = c.addComponent<RotationForce>(e);
    Velocity &vel = c.addComponent<Velocity>(e);
    Rotation &rot = c.addComponent<Rotation>(e);
    // BoundingBox &bbComponent = c.addComponent<BoundingBox>(e);
    Physic &phy = c.addComponent<Physic>(e);
    Lifetime &life = c.addComponent<Lifetime>(e);

    // bbComponent.set(Vector3d(64.0f, 64.0f, 0.0f));
    phy.fixed = true;
    vel.velocity = Vector3d(60.0f, 60.0f, 0.0f);
    posComponent.position = position;
    imgComponent.img = ResourceManager::getInstance().get<Image>("stars.png");
    scaleComponent.scale = Vector3d(64.0f, 64.0f, 0.0f);
    rotForce.force = Vector3d(0.0f, 0.0f, 25.0f);
    colorComponent.set(0.5f, 0.2f, 0.0f, 1.0f);
    life.time = 3.0f;

    (void)rot;
    return e;
  }

  virtual void			update(unsigned int entity, float time, const ALLEGRO_EVENT &)
  {
    Pistol			*pistol = ComponentManager::getInstance().getComponent<Pistol>(entity);
    InputSystem			*sys = SystemManager::getInstance().getSystem<InputSystem>();
 
    if (!pistol)
      return;

    if (pistol->fireRateCache > 0.0f)
      {
	pistol->fireRateCache -= time;
	return;
      }

    if (!sys->isDown(ALLEGRO_KEY_SPACE)) 
      return;

    Position			*position = ComponentManager::getInstance().getComponent<Position>(entity);

    if (pistol->fireRateCache <= 0.0f)
      {
	pistol->fireRateCache = pistol->fireRate;
      }

    unsigned int b = createBullet(position->position);
    std::cout << "New bullet : " << b << std::endl;
    (void)b;
  }
private:
};

#endif				// __PISTOL_SYSTEM_HPP__
