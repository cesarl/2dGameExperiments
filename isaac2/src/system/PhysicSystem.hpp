#ifndef				__PHYSIC_SYSTEM_HPP__
# define			__PHYSIC_SYSTEM_HPP__

#include			<limits>
#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

class				PhysicSystem : public System
{
public:
  virtual ~PhysicSystem(){};
  PhysicSystem()
  {}
  void				init()
  {
    require<Physic>();
    require<Collision>();
    require<Velocity>();
  }


  // bool				stillCollide(unsigned int e1, unsigned int e2)
  // {
  //   BoundingBox			*bb1 = ComponentManager::getInstance().getComponent<BoundingBox>(entity);
  //   BoundingBox			*bb2 = ComponentManager::getInstance().getComponent<BoundingBox>(entity);
  // }

  virtual void			update(EntityData &entity, float time, const ALLEGRO_EVENT &)
  {
    Physic			*phy = ComponentManager::getInstance().getComponent<Physic>(entity);

    if (phy->fixed)
      return;

    BoundingBox			*bb1 = ComponentManager::getInstance().getComponent<BoundingBox>(entity);
    Collision			*col1 = ComponentManager::getInstance().getComponent<Collision>(entity);
    Velocity			*vel1 = ComponentManager::getInstance().getComponent<Velocity>(entity);



    for (std::list<unsigned int>::iterator it = col1->list.begin();
	 it != col1->list.end();
	 ++it)
      {

	if (!BoundingBoxSystem::collide(entity, EntityManager::getInstance().getEntityData(*it)))
	  continue;

	BoundingBox		*bb2 = ComponentManager::getInstance().getComponent<BoundingBox>(*it);

	float xInvEntry, yInvEntry;

	// compute distance
	if (vel1->velocity.x * time > 0.0f)
	  {
	    xInvEntry = bb2->pastFrom.x - bb1->pastTo.x;
	  }
	else 
	  {
	    xInvEntry = bb2->pastTo.x - bb1->pastFrom.x;
	  }

	if (vel1->velocity.y * time > 0.0f)
	  {
	    yInvEntry = bb2->pastFrom.y - bb1->pastTo.y;
	  }
	else
	  {
	    yInvEntry = bb2->pastTo.y - bb1->pastFrom.y;
	  }

	// time of collision and time of leaving for each axes
	float xEntry, yEntry;

	if (vel1->velocity.x == 0)
	  {
	    xEntry = - std::numeric_limits<float>::infinity();
	  }
	else
	  {
	    xEntry = xInvEntry / (vel1->velocity.x * time);
	  }

	if (vel1->velocity.y == 0)
	  {
	    yEntry = - std::numeric_limits<float>::infinity();
	  }
	else
	  {
	    yEntry = yInvEntry / (vel1->velocity.y * time);
	  }
	
	float entryTime = std::max(xEntry, yEntry);
	float normalx, normaly;

	if (xEntry > yEntry)
	  {
	    if (xInvEntry < 0.0f)
	      {
		normalx = 1.0f;
		normaly = 0.0f;
	      }
	    else
	      {
		normalx = -1.0f;
		normaly = 0.0f;
	      }
	  }
	else
	  {
	    if (yInvEntry < 0.0f)
	      {
		normalx = 0.0f;
		normaly = 1.0f;
	      }
	    else
	      {
		normalx = 0.0f;
		normaly = -1.0f;
	      }
	  }

	response(entity, entryTime, time, normalx, normaly);
      }
  }

  void				response(const EntityData &entity, float difTime, float time, float normalX, float normalY)
  {
    Position			*pos = ComponentManager::getInstance().getComponent<Position>(entity);
    Velocity			*vel = ComponentManager::getInstance().getComponent<Velocity>(entity);

    if (vel->velocity.x != 0)
      pos->position.x += vel->velocity.x * (difTime - 0.1) * time;
    if (vel->velocity.y != 0)
      pos->position.y += vel->velocity.y * (difTime - 0.1) * time;

    Vector3d n = Vector3d(normalX, normalY, 0.0f);
    Vector3d im = (Vector3d(0.0f, 0.0f, 0.0f) - (vel->velocity * n)) * n;
    vel->velocity += im;
    BoundingBoxSystem::updateBoundingBox(entity, time);
  }

private:
};

#endif				// __PHYSIC_SYSTEM_HPP__
