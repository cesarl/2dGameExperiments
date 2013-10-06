#ifndef				__BB_SYSTEM_HPP__
# define			__BB_SYSTEM_HPP__

#include            <unordered_set>
#include			"System.hpp"
#include			"EntityData.hpp"
#include			"TagIdManager.hpp"

class				BoundingBoxSystem : public System
{
public:
	virtual ~BoundingBoxSystem(){};
	BoundingBoxSystem() :
		System(),
		side_(64 * 3)
	{}
	void				init()
	{
		require<Position>();
		require<BoundingBox>();
	}

	void				addException(const std::string &layer1, const std::string &layer2)
	{
		unsigned int		l1 = TagIdManager::getInstance().getTagId(layer1);
		unsigned int		l2 = TagIdManager::getInstance().getTagId(layer2);
		unsigned int s = l1 < l2 ? l1 * 1000 + l2 : l2 * 1000 + l1;
		exceptions_.insert(s);
	}

	bool				isLayerCollidable(EntityData &e1, EntityData &e2)
	{
		unsigned int al = e1.getLayer();
		unsigned int bl = e2.getLayer();

		unsigned int s = al < bl ? al * 1000 + bl : bl * 1000 + al;

		std::unordered_set<unsigned int>::iterator it;
		it = exceptions_.find(s);
		return (it == exceptions_.end());
	}

	static void			updateBoundingBox(const EntityData &entity, float time)
	{
		BoundingBox			*bb = entity.getComponent<BoundingBox>();
		Position			*pos = entity.getComponent<Position>();

		bb->from = pos->position;
		bb->from += bb->offset;

		bb->pastFrom = bb->from;
		bb->pastTo = bb->from;
		bb->pastTo += bb->size;

		if (entity.hasComponent<Velocity>())
		{
			Velocity		*vel = entity.getComponent<Velocity>();
			glm::vec3		v = vel->velocity;
			v *= time;
			bb->from +=  v;
		}

		bb->to = bb->from;
		bb->to += bb->size;
	}

	virtual void			update(EntityData &entity, float time, const ALLEGRO_EVENT &ev)
	{
		if (ev.type != ALLEGRO_EVENT_TIMER)
			return;

		BoundingBox			*bb = entity.getComponent<BoundingBox>();

		updateBoundingBox(entity, time);

		// if (col)
		//   {
		// 	col->list.clear();
		// 	entity.removeComponent<Collision>();
		//   }

		glm::vec3 from = bb->from;
		from /= glm::vec3(side_, side_, 0);
		glm::vec3 to = bb->to;
		to /= glm::vec3(side_, side_, 0);

		for (int i = from.x; i <= to.x; ++i)
		{
			for (int j = from.y; j <= to.y; ++j)
			{
				int key = i * 10000 + j;
				std::map<int, std::list<unsigned int> >::iterator it = list_.find(key);
				if (it != list_.end())
				{
					it->second.push_back(entity.id);
				}
				else
				{
					std::list<unsigned int> newList;

					newList.push_back(entity.id);
					list_.insert(std::pair<int, std::list<unsigned int> >(key, newList));
				}
			}
		}
	}

	virtual void			updateBegin(float, const ALLEGRO_EVENT &)
	{
		std::map<int, std::list<unsigned int> >::iterator it;

		it = list_.begin();
		while (it != list_.end())
		{
			std::list<unsigned int>::iterator it2 = it->second.begin();

			while (it2 != it->second.end())
			{
				Collision		*col = EntityManager::getInstance().getEntityData(*it2).getComponent<Collision>();

				if (col)
				{
					col->list.clear();
					EntityManager::getInstance().getEntityData(*it2).removeComponent<Collision>();
				}
				++it2;
			}
			it->second.clear();
			++it;
		}
	};

	static bool			collide(const EntityData &e1, const EntityData &e2)
	{
		BoundingBox			*bb1 = e1.getComponent<BoundingBox>();
		BoundingBox			*bb2 = e2.getComponent<BoundingBox>();

		if (!bb1 || !bb2)
			return false;

		if (bb1->from.x > bb2->to.x ||
			bb1->to.x < bb2->from.x ||
			bb1->from.y > bb2->to.y ||
			bb1->to.y < bb2->from.y)
			return false;
		return true;
	}

	void				addCollisionComponent(unsigned int e1, unsigned int e2)
	{
		Collision			*c1 = EntityManager::getInstance().getEntityData(e1).getComponent<Collision>();
		Collision			*c2 = EntityManager::getInstance().getEntityData(e2).getComponent<Collision>();
		// Position			*p1 = ComponentManager::getInstance().getComponent<Position>(e1);
		// Position			*p2 = ComponentManager::getInstance().getComponent<Position>(e2);

		if (!c1)
			c1 = EntityManager::getInstance().getEntityData(e1).addComponent<Collision>();
		if (!c2)
			c2 = EntityManager::getInstance().getEntityData(e2).addComponent<Collision>();
		EntityData &ee1 = EntityManager::getInstance().getEntityData(e1);
		EntityData &ee2 = EntityManager::getInstance().getEntityData(e2);
		ee1.addComponent<RotationForce>()->force = glm::vec3(1.0f, -1.0f, 0.5f);
		ee2.addComponent<RotationForce>()->force = glm::vec3(1.0f, -1.0f, 0.5f);
		c1->list.push_back(e2);
		c2->list.push_back(e1);
	}

	virtual void			updateEnd(float, const ALLEGRO_EVENT &)
	{
		std::map<int, std::list<unsigned int> >::iterator it;
		static EntityManager	&mgr = EntityManager::getInstance();

		it = list_.begin();
		while (it != list_.end())
		{
			std::list<unsigned int>::iterator one = it->second.begin();
			while (one != it->second.end())
			{
				std::list<unsigned int>::iterator two = --it->second.end();
				while (two != one)
				{
					EntityData &e1 = mgr.getEntityData(*one);
					EntityData &e2 = mgr.getEntityData(*two);
					if (*one != *two && isLayerCollidable(e1, e2) && collide(e1, e2))
						addCollisionComponent(*one, *two);
					--two;
				}
				++one;
			}
			++it;
		}
	};

private:
	unsigned int			side_;
	std::map<int, std::list<unsigned int> > list_;
	std::unordered_set<unsigned int>	exceptions_;
};

#endif				// __BB_SYSTEM_HPP__
