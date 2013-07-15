#ifndef				__BB_SYSTEM_HPP__
# define			__BB_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

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


  static void			updateBoundingBox(unsigned int entity, float time)
  {
    BoundingBox			*bb = ComponentManager::getInstance().getComponent<BoundingBox>(entity);
    Position			*pos = ComponentManager::getInstance().getComponent<Position>(entity);
    Velocity			*vel = ComponentManager::getInstance().getComponent<Velocity>(entity);

    bb->from = pos->position;
    bb->from += bb->offset;

    bb->pastFrom = bb->from;
    bb->pastTo = bb->from;
    bb->pastTo += bb->size;

    if (vel)
      {
	Vector3d v = vel->velocity;
	v *= time;
	bb->from +=  v;
      }

    bb->to = bb->from;
    bb->to += bb->size;
  }

  virtual void			update(unsigned int entity, float time, const ALLEGRO_EVENT &ev)
  {
    if (ev.type != ALLEGRO_EVENT_TIMER)
      return;

    BoundingBox			*bb = ComponentManager::getInstance().getComponent<BoundingBox>(entity);
    Collision			*col = ComponentManager::getInstance().getComponent<Collision>(entity);

    updateBoundingBox(entity, time);

    if (col)
      {
	col->list.clear();
	ComponentManager::getInstance().removeComponent<Collision>(entity);
      }

    Vector3d from = bb->from;
    from /= Vector3d(side_, side_, 0);
    Vector3d to = bb->to;
    to /= Vector3d(side_, side_, 0);

    for (int i = from.x; i <= to.x; ++i)
      {
	for (int j = from.y; j <= to.y; ++j)
	  {
	    int key = i * 10000 + j;
	    std::map<int, std::list<unsigned int> >::iterator it = list_.find(key);
	    if (it != list_.end())
	      {
		it->second.push_back(entity);
	      }
	    else
	      {
		std::list<unsigned int> newList;
		
		newList.push_back(entity);
		list_.insert(std::pair<int, std::list<unsigned int> >(key, newList));
	      }
	  }
      }
  }

  virtual void			updateBegin()
  {
    std::map<int, std::list<unsigned int> >::iterator it;

    it = list_.begin();
    while (it != list_.end())
      {
	it->second.clear();
	++it;
      }
  };
  
  static bool			collide(unsigned int e1, unsigned int e2)
  {
    BoundingBox			*bb1 = ComponentManager::getInstance().getComponent<BoundingBox>(e1);
    BoundingBox			*bb2 = ComponentManager::getInstance().getComponent<BoundingBox>(e2);

    if (bb1->from.x > bb2->to.x ||
	bb1->to.x < bb2->from.x ||
	bb1->from.y > bb2->to.y ||
	bb1->to.y < bb2->from.y)
      return false;
    return true;
  }

  void				addCollisionComponent(unsigned int e1, unsigned int e2)
  {
    Collision			*c1 = ComponentManager::getInstance().getComponent<Collision>(e1);
    Collision			*c2 = ComponentManager::getInstance().getComponent<Collision>(e2);
    // Position			*p1 = ComponentManager::getInstance().getComponent<Position>(e1);
    // Position			*p2 = ComponentManager::getInstance().getComponent<Position>(e2);

    if (!c1)
      ComponentManager::getInstance().addComponent<Collision>(e1);
    if (!c2)
      ComponentManager::getInstance().addComponent<Collision>(e2);

    c1 = ComponentManager::getInstance().getComponent<Collision>(e1);
    c2 = ComponentManager::getInstance().getComponent<Collision>(e2);

    c1->list.push_back(e2);
    c2->list.push_back(e1);
  }

  virtual void			updateEnd()
  {
    std::map<int, std::list<unsigned int> >::iterator it;

    it = list_.begin();
    while (it != list_.end())
      {
	std::list<unsigned int>::iterator one = it->second.begin();
	while (one != it->second.end())
	  {
	    std::list<unsigned int>::iterator two = --it->second.end();
	    while (two != one)
	      {
		if (*one != *two && collide(*one, *two))
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
};

#endif				// __BB_SYSTEM_HPP__
