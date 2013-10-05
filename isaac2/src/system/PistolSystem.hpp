#ifndef				__PISTOL_SYSTEM_HPP__
# define			__PISTOL_SYSTEM_HPP__

#include			"System.hpp"
#include            "EntityManager.hpp"
#include            "SystemManager.hpp"

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
    require<Velocity>();
  }


  unsigned int			createBullet(const glm::vec3 & position, const glm::vec3 & dir, EntityData &entity)
  {
    EntityData   		&e = EntityManager::getInstance().newEntity();

    e.setLayer("Good");

    Position *posComponent = e.addComponent<Position>();
    // Img &imgComponent = c.addComponent<Img>(e);
    Sprite *spriteComponent = e.addComponent<Sprite>();
    Scale *scaleComponent = e.addComponent<Scale>();
    Color *colorComponent = e.addComponent<Color>();
    RotationForce *rotForce = e.addComponent<RotationForce>();
    Velocity *vel = e.addComponent<Velocity>();
    Rotation *rot = e.addComponent<Rotation>();
    BoundingBox *bbComponent = e.addComponent<BoundingBox>();
    Physic *phy = e.addComponent<Physic>();
    Lifetime *life = e.addComponent<Lifetime>();

    e.addComponent<VelocityFriction>()->friction = 0.9999f;
    bbComponent->set(glm::vec3(32.0f, 32.0f, 0.0f));
    phy->fixed = false;
    vel->velocity = dir;
    vel->velocity *= 700.0f;
    Velocity *v = entity.getComponent<Velocity>();
    if (!v)
      std::cout << "YA PAS DE VELOCITY !!!! WTF !!!" << std::endl;
    else
      vel->velocity += v->velocity;

    posComponent->position = position;
    posComponent->position.z = 1000;
    spriteComponent->animation = ResourceManager::getInstance().get<AnimationMedia>("test.anim");
    scaleComponent->scale = glm::vec3(32.0f, 32.0f, 0.0f);
    rotForce->force = glm::vec3(0.0f, 0.0f, 25.0f);
    *colorComponent = (Color(1.0f, 1.0f, 1.0f, 1.0f));
    life->time = 3.0f;

    (void)rot;
    return e.id;
  }

  virtual void			update(EntityData &entity, float time, const ALLEGRO_EVENT &)
  {
    Pistol			*pistol = entity.getComponent<Pistol>();
    static InputSystem		*sys = SystemManager::getInstance().getSystem<InputSystem>();
 
    if (!pistol)
      return;

    if (pistol->fireRateCache > 0.0f)
      {
	pistol->fireRateCache -= time;
	return;
      }

    unsigned int b = 0;
    glm::vec3 dir;
    Position			*position = entity.getComponent<Position>();

    if (sys->isDown(ALLEGRO_KEY_LEFT)
	&& sys->isDown(ALLEGRO_KEY_UP)) // left up
      {
	b = createBullet(position->position, glm::vec3(-1, 1, 0), entity);
      }
    else if (sys->isDown(ALLEGRO_KEY_LEFT)
	     && sys->isDown(ALLEGRO_KEY_DOWN)) // left down
      {
	b = createBullet(position->position, glm::vec3(-1, -1, 0), entity);
      }
    else if (sys->isDown(ALLEGRO_KEY_RIGHT)
	     && sys->isDown(ALLEGRO_KEY_UP)) // right up
      {
	b = createBullet(position->position, glm::vec3(1, 1, 0), entity);
      }
    else if (sys->isDown(ALLEGRO_KEY_RIGHT)
	     && sys->isDown(ALLEGRO_KEY_DOWN)) // right down
      {
	b = createBullet(position->position, glm::vec3(1, -1, 0), entity);
      }
    else if (sys->isDown(ALLEGRO_KEY_LEFT)) // left
      {
	b = createBullet(position->position, glm::vec3(-1, 0, 0), entity);
      }
    else if (sys->isDown(ALLEGRO_KEY_RIGHT)) // right
      {
	b = createBullet(position->position, glm::vec3(1, 0, 0), entity);
      }
    else if (sys->isDown(ALLEGRO_KEY_UP)) // up
      {
	b = createBullet(position->position, glm::vec3(0, 1, 0), entity);
      }
    else if (sys->isDown(ALLEGRO_KEY_DOWN)) // down
      {
	b = createBullet(position->position, glm::vec3(0, -1, 0), entity);
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
