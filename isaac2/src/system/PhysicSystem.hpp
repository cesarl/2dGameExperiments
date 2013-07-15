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

  virtual void			update(unsigned int entity, float time, const ALLEGRO_EVENT &)
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

	if (!BoundingBoxSystem::collide(entity, *it))
	  continue;

	BoundingBox		*bb2 = ComponentManager::getInstance().getComponent<BoundingBox>(*it);

	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// compute distance
	if (vel1->velocity.x * time > 0.0f)
	  {
	    xInvEntry = bb2->pastFrom.x - bb1->pastTo.x;
	    xInvExit = bb2->pastTo.x - bb1->pastFrom.x;
	  }
	else 
	  {
	    xInvEntry = bb2->pastTo.x - bb1->pastFrom.x;
	    xInvExit = bb2->pastFrom.x - bb1->pastTo.x;
	  }

	if (vel1->velocity.y * time > 0.0f)
	  {
	    yInvEntry = bb2->pastFrom.y - bb1->pastTo.y;
	    yInvExit = bb2->pastTo.y - bb1->pastFrom.y;
	  }
	else
	  {
	    yInvEntry = bb2->pastTo.y - bb1->pastFrom.y;
	    yInvExit = bb2->pastFrom.y - bb1->pastTo.y;
	  }

	// time of collision and time of leaving for each axes
	float xEntry, yEntry;
	float xExit, yExit;

	if (vel1->velocity.x == 0)
	  {
	    xEntry = - std::numeric_limits<float>::infinity();
	    xExit = std::numeric_limits<float>::infinity();
	  }
	else
	  {
	    xEntry = xInvEntry / (vel1->velocity.x * time);
	    xExit = xInvExit / (vel1->velocity.x * time);
	  }

	if (vel1->velocity.y == 0)
	  {
	    yEntry = - std::numeric_limits<float>::infinity();
	    yExit = std::numeric_limits<float>::infinity();
	  }
	else
	  {
	    yEntry = yInvEntry / (vel1->velocity.y * time);
	    yExit = yInvExit / (vel1->velocity.y * time);
	  }

	// find the earliest and latest times of collision
	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);
	float normalx, normaly;

	// if there was no collision
	// if (entryTime > exitTime || (xEntry < 0.0f && yEntry < 0.0f) || xEntry > 1.0f || yEntry > 1.0f)
	//   {
	//     normalx = 0.0f;
	//     normaly = 0.0f;

	//     continue;
	//   }
	// else //if there was a collision
	(void)exitTime;
	  {        
	    // calculate normal of collided surface
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
	  }
	  response(entity, entryTime, time, normalx, normaly);
	  //break;
      }
  }

  void				response(unsigned int entity, float difTime, float time, float normalX, float normalY)
  {
    Position			*pos = ComponentManager::getInstance().getComponent<Position>(entity);
    Velocity			*vel = ComponentManager::getInstance().getComponent<Velocity>(entity);
    // float			remainingTime = 1.0f - difTime;

    // if (difTime > 1.0f)
    //   return;



    if (vel->velocity.x != 0)
      pos->position.x += vel->velocity.x * (difTime - 0.1) * time;
    if (vel->velocity.y != 0)
      pos->position.y += vel->velocity.y * (difTime - 0.1) * time;



    float dotprod = (vel->velocity.x * normalY + vel->velocity.y * normalX);
    // if (dotprod > 0.0f)
    //   dotprod = 1.0f;
    // else if (dotprod < 0.0f)
    //   dotprod = -1.0f;


    Vector3d n = Vector3d(normalX, normalY, 0.0f);
    Vector3d im = Vector3d(0.0f, 0.0f, 0.0f) - (vel->velocity * n) * n;
    vel->velocity += im;
    (void)dotprod;
    // if (dotprod == dotprod)
    //   {
    // 	vel->velocity.x = dotprod * normalY;
    // 	vel->velocity.y = dotprod * normalX;
    //   }


    // if (normalX != 0.0f)
    //   vel->velocity.x *= -0.5f;
    // if (normalY != 0.0f)
    //   vel->velocity.y *= -0.5f;


      


    BoundingBoxSystem::updateBoundingBox(entity, time);

    // if (vel->velocity.x * normalY + vel->velocity.y * normalX != 0.0f)
    //   {
    // 	float dotprod = (vel->velocity.x * normalY + vel->velocity.y * normalX) * (1.0f - difTime);


    // 	vel->velocity.x = dotprod * normalY;
    // 	vel->velocity.y = dotprod * normalX;

    //   }
    // else
    //   {
    // 	vel->velocity.x *= (1.0f - difTime);
    // 	vel->velocity.y *= (1.0f - difTime);
    // 	if (abs(normalX) > 0.0001f)
    // 	  vel->velocity.x *= -1.0f;
    // 	if (abs(normalY) > 0.0001f)
    // 	  vel->velocity.y *= -1.0f;
      // }

    // if (normalX != 0.0f)
    //   vel->velocity.x *= -1.0f;
    // if (normalY != 0.0f)
    //   vel->velocity.y *= -1.0f;

    (void)entity;
    (void)time;
    (void)pos;
    (void)difTime;
    (void)normalX;
    (void)normalY;
  }

  virtual void			updateBegin(){};
  virtual void			updateEnd(){};

private:
};

#endif				// __PHYSIC_SYSTEM_HPP__
