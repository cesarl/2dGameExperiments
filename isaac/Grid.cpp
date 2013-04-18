#include			"Grid.hh"
#include			"CollisionManager.hh"

Grid::Grid(int cellSize) :
  cellSize_(cellSize),
  height_(0),
  width_(0),
  maxWidth_(10000)
{}

Grid::~Grid()
{
  this->clear();
}

void				Grid::update()
{
  t_cell_iter			it;
  t_iter			cit;
  t_iter			citend;

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
	      // (*cit)->update();
	      if (cit != citend && BOUNDING_BOX(*cit)->collide(*citend))
		{
		  CollisionManager::getInstance()->resolveCollision(*cit, *citend);
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
}

void				Grid::add(Entity *entity)
{
  BoundingBox			*bb = BOUNDING_BOX(entity);
  int				minX;
  int				maxX;
  int				minY;
  int				maxY;
  int				key;
  t_cell_iter			it;
  std::list<Entity*>		newList;

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

void				Grid::remove(Entity *entity)
{
  Position			*pos = POSITION(entity);
  int				key = pos->x * this->maxWidth_ + pos->y;
  t_cell_iter			it;

  it = this->list_.find(key);
  if (it != this->list_.end())
    {
      it->second.remove(entity);
    }
  (void)entity;
}

void				Grid::clear()
{
  t_cell_iter			it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      it->second.clear();
      ++it;
    }
  this->list_.clear();
}
