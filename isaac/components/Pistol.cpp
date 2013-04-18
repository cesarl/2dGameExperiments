#include				"Pistol.hh"
#include				"ComponentTypes.hh"
#include				"Grid.hh"
#include				"DrawCollection.hh"

#include				<iostream> //pour le debug - a virer

Pistol::Pistol(Entity *entity) :
  AComponent(entity, T_PISTOL, 1),
  fireRate_(0.8),
  friction_(0.3),
  speedBullet_(10),
  bulletLifeTime_(3),
  shootTime_(al_get_time()),
  gridCollision_(NULL),
  drawCollection_(NULL)
{
}

Pistol::~Pistol()
{
  // todo clear la pool provisoire - ca leak ^^
}

void					Pistol::update(double time)
{
  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;

  std::vector<Entity*>::iterator	it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      (*it)->update();
      if (!VISIBILITY(this->entity)->visible)
	{
	  if (this->gridCollision_)
	    {
	      this->gridCollision_->remove(*it);
	    }
	  if (this->drawCollection_)
	    {
	      this->drawCollection_->remove(*it);
	    }
	  delete *it;
	  it = this->list_.erase(it);
	}
      else
	{
	  if (this->gridCollision_)
	    {
	      this->gridCollision_->add(*it);
	    }
	  if (this->drawCollection_)
	    this->drawCollection_->add(*it, 2);
	  ++it;
	}
    }
}

void					Pistol::attachGridCollision(Grid *grid)
{
  this->gridCollision_ = grid;
}

void					Pistol::attachDrawCollection(DrawCollection *drawCollection)
{
  this->drawCollection_ = drawCollection;
}

void					Pistol::draw()
{
  std::vector<Entity*>::iterator	it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      (*it)->draw();
      ++it;
    }
}

bool					Pistol::fire(float vx, float vy)
{
  if (al_get_time() - this->shootTime_ < this->fireRate_)
    return false;

  Entity				*tmp;

  tmp = new Entity;
  POSITION(tmp)->setPos(BOUNDING_BOX(this->entity)->getCenterX() - 15, BOUNDING_BOX(this->entity)->getCenterY() - 15);
  MOVE(tmp)->setDirection(vx * this->speedBullet_, vy * this->speedBullet_);
  MOVE(tmp)->setFriction(this->friction_, this->friction_);
  VISIBILITY(tmp)->fadeOut(0.3, 10);
  IMAGE(tmp)->setBitmap("assets/imgs/bullet.png");
  ROTATION_FORCE(tmp)->launch(0.5, 0.005);
  FORCE_RESISTANCE(tmp)->setResistance(1);
  BOUNDING_BOX(tmp)->setDimension(24, 24);
  BOUNDING_BOX(tmp)->setMargin(3, 3);
  DAMAGE(tmp)->setMagnitude(5);
  DANGER_TYPE(tmp)->setType(GOOD);
  COLLISION_TYPE(tmp)->setType(BULLET);
  *TEXT(tmp) = "bullet";

  this->shootTime_ = al_get_time();
  this->list_.push_back(tmp);
  return true;
}
