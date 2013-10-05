#ifndef				__BULLET_SYSTEM_HPP__
# define			__BULLET_SYSTEM_HPP__

#include			"System.hpp"
#include			"Components.hpp"
#include			"TagIdManager.hpp"

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
		require<Collision>();
		require<Velocity>();
		require<BoundingBox>();
		require<RotationForce>();
	}

	virtual void			update(EntityData &entity, float, const ALLEGRO_EVENT &)
	{
		static unsigned int		wallTag = TagIdManager::getInstance().getTagId("Wall");
		Collision			*col = entity.getComponent<Collision>();

		unsigned int tag = EntityManager::getInstance().getEntityData(col->list.front()).getTag();
		if (tag == wallTag)
		{
			entity.getComponent<Position>(entity)->position.z = 3;
			entity.removeComponent<RotationForce>();
			entity.removeComponent<BoundingBox>();
			entity.removeComponent<Velocity>();
			entity.addComponent<ColorEasing>();
			entity.getComponent<ColorEasing>()->setEasing(Color(0.0f, 1.0f, 0.0f, 0.1f), 10.0f, entity);

			Lifetime			*life = entity.getComponent<Lifetime>();
			life->time = 0.0f;
		}
	}
private:
};

#endif				// __BULLET_SYSTEM_HPP__
