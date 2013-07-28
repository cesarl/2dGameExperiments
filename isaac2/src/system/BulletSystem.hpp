#ifndef				__BULLET_SYSTEM_HPP__
# define			__BULLET_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

class				BulletSystem : public System
{
public:
  virtual ~BulletSystem()
  {}

  BulletSystem()
  {}

  void				init()
  {
    require<Lifetime>();
  }

  virtual void			update(unsigned int entity, float, const ALLEGRO_EVENT &)
  {
    Collision			*col = ComponentManager::getInstance().getComponent<Collision>(entity);

    if (col)
      {
	std::string tag = EntityManager::getInstance().getEntityData(col->list.front()).getTag();

	if (tag == "Wall")
	  {
	    std::cout << "lol " << std::endl;
	    ComponentManager::getInstance().getComponent<Position>(entity)->position.z = 3;
	    ComponentManager::getInstance().removeComponent<RotationForce>(entity);
	    ComponentManager::getInstance().removeComponent<BoundingBox>(entity);
	    ComponentManager::getInstance().removeComponent<Velocity>(entity);
	    ComponentManager::getInstance().addComponent<ColorEasing>(entity);
	    ComponentManager::getInstance().getComponent<ColorEasing>(entity)->setEasing(Color(1.0f, 0.0f, 0.0f, 1.0f), 10.0f);
	  }
	return;
      }

    Lifetime			*life = ComponentManager::getInstance().getComponent<Lifetime>(entity);

    life->time = 0.0f;
  }
private:
};

#endif				// __BULLET_SYSTEM_HPP__
