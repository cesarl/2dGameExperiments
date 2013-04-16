#include				"Pistol.hh"
#include				"ComponentTypes.hh"
#include				"Grid.hh"

#include				<iostream> //pour le debug - a virer

Pistol::Pistol(Entity *entity) :
  AComponent(entity, T_PISTOL, 1),
  fireRate_(0.8),
  friction_(0.3),
  speedBullet_(10),
  bulletLifeTime_(3),
  shootTime_(al_get_time()),
  grid_(NULL)
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
      if (!VISIBILITY(*it)->visible)
	{
	  if (this->grid_)
	    this->grid_->remove(*it);
	  delete *it;
	  it = this->list_.erase(it);
	}
      else
	{
	  if (this->grid_)
	    this->grid_->add(*it);
	  ++it;
	}
    }
}

void					Pistol::attachGrid(Grid *grid)
{
  this->grid_ = grid;
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
  POSITION(tmp)->setPos(POSITION(this->entity)->x, POSITION(this->entity)->y);
  MOVE(tmp)->setDirection(vx * this->speedBullet_, vy * this->speedBullet_);
  MOVE(tmp)->setFriction(this->friction_, this->friction_);
  VISIBILITY(tmp)->fadeOut(0.3, 10);
  SPRITE(tmp)->config(8, 64, 64, 8, 8, 8, 0.12);
  IMAGE(tmp)->setBitmap("assets/imgs/mummy.png");
  ROTATION_FORCE(tmp)->launch((float)rand()/RAND_MAX/2 - 0.5, 0.005);
  FORCE_RESISTANCE(tmp)->setResistance(1);
  BOUNDING_BOX(tmp)->setDimension(30, 30);
  BOUNDING_BOX(tmp)->setMargin(17, 17);

  this->shootTime_ = al_get_time();
  this->list_.push_back(tmp);
  return true;
}
