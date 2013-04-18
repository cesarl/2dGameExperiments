#include				"CollisionManager.hh"

#include				<iostream> // pour debug - a virer

CollisionManager::CollisionManager()
{}

CollisionManager::~CollisionManager()
{}

CollisionManager			*CollisionManager::getInstance()
{
  static CollisionManager		that;
  return &that;
}

void					CollisionManager::resolveCollision(Entity *e1, Entity *e2)
{
  t_collisionType			t1 = COLLISION_TYPE(e1)->getType();
  t_collisionType			t2 = COLLISION_TYPE(e2)->getType();
  t_dangerType				d1 = DANGER_TYPE(e1)->getType();
  t_dangerType				d2 = DANGER_TYPE(e2)->getType();
  BoundingBox				*b1 = BOUNDING_BOX(e1);
  BoundingBox				*b2 = BOUNDING_BOX(e2);

  // same type - no consequences
  if ((d1 == GOOD || d1 == BAD) && d1 == d2)
    {
      // std::cout << "same type" << std::endl;
      return;
    }


  // apply damages to health
  if (e1->hasComponent(T_DAMAGE))
    {
      if (e2->hasComponent(T_HEALTH))
      	{
	  // std::cout << "-"<< TEXT(e1)->text << " put damage on " << TEXT(e2)->text << " : " << d1 << " " << d2<<std::endl;
      	  HEALTH(e2)->impactDamage(e1);
      	}
      DAMAGE(e1)->applied();
    }
  if (e2->hasComponent(T_DAMAGE))
    {
      if (e1->hasComponent(T_HEALTH))
      	{
	  // std::cout << "+" << TEXT(e2)->text << " put damage on " << TEXT(e1)->text << " : " << d2 << " " << d1<<std::endl;
      	  HEALTH(e1)->impactDamage(e2);
      	}
      DAMAGE(e2)->applied();
    }
  if (t1 == FIX_GO)
    {
      POSITION(e2)->reversePos();
      MOVE(e2)->reverseOneAxe(abs(b2->getCenterX() - b1->getCenterX()), abs(b2->getCenterY() - b1->getCenterY()), 0.3);
    }
  if (t2 == FIX_GO)
    {
      POSITION(e1)->reversePos();
      MOVE(e1)->reverseOneAxe(abs(b2->getCenterX() - b1->getCenterX()), abs(b2->getCenterY() - b1->getCenterY()), 0.3);
    }
}

