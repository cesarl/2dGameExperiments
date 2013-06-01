#include				"CollisionManager.hh"

#include				<iostream> // pour debug - a virer

CollisionManager::CollisionManager() :
  cellSize_(100),
  height_(0),
  width_(0),
  maxWidth_(10000)
{}

CollisionManager::~CollisionManager()
{
  this->clear();
}

CollisionManager			*CollisionManager::getInstance()
{
  static CollisionManager		that;
  return &that;
}

void					CollisionManager::update()
{
  t_cell_iter				it;
  t_iter				cit;
  t_iter				citend;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      if (it->second.empty())
	continue;
      cit = it->second.begin();
      while (cit != it->second.end())
	{
	  citend = --(it->second.end());
	  while (citend != cit)
	    {
	      if (cit != citend && BOUNDING_BOX(*cit)->collide(*citend))
		{
		  this->resolveCollision(*cit, *citend);
		  // FORCE_RESISTANCE(*citend)->applyForce(*cit);
		  // POSITION(*cit)->reversePos();
		  // POSITION(*citend)->reversePos();
		}
	      --citend;
	    }
	  ++cit;
	}
      ++it;
    }
  this->clear();
}

void					CollisionManager::add(Entity *entity)
{
  BoundingBox				*bb;
  int					minX;
  int					maxX;
  int					minY;
  int					maxY;
  int					key;
  t_cell_iter				it;
  std::list<Entity*>			newList;

  if (!entity->hasComponent(T_BOUNDING_BOX))
    {
      return;
    }
  bb = BOUNDING_BOX(entity);
  minX = bb->getX() / this->cellSize_;
  maxX = bb->getXX() / this->cellSize_;
  maxY = bb->getYY() / this->cellSize_ * this->maxWidth_;
  while (minX <= maxX)
    {
      minY = bb->getY() / this->cellSize_ * this->maxWidth_;
      while (minY <= maxY)
	{
	  key = minX + minY;
	  it = this->list_.find(key);
	  if (it != this->list_.end())
	    {
	      it->second.push_back(entity);
	    }
	  else
	    {
	      newList.push_back(entity);
	      this->list_.insert(std::pair<int, std::list<Entity*> >(key, newList));
	    }
	  minY += this->maxWidth_;
	}
      ++minX;
    }
}

void					CollisionManager::remove(Entity *entity)
{
  Position				*pos = POSITION(entity);
  int					key = pos->x * this->maxWidth_ + pos->y;
  t_cell_iter				it;

  it = this->list_.find(key);
  if (it != this->list_.end())
    {
      it->second.remove(entity);
    }
}

void					CollisionManager::clear()
{
  t_cell_iter				it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      it->second.clear();
      ++it;
    }
  this->list_.clear();
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
      if (DAMAGE(e1)->canDamage() && e2->hasComponent(T_HEALTH))
      	{
	  // std::cout << "-"<< TEXT(e1)->text << " put damage on " << TEXT(e2)->text << " : " << d1 << " " << d2<<std::endl;
      	  HEALTH(e2)->impactDamage(e1);
      	}
      DAMAGE(e1)->applied();
    }
  if (e2->hasComponent(T_DAMAGE))
    {
      if (DAMAGE(e2)->canDamage() && e1->hasComponent(T_HEALTH))
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
