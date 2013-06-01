#include				"Pistol.hh"
#include				"ComponentTypes.hh"
#include				"DrawManager.hh"
#include				"CollisionManager.hh"

#include				<iostream> //pour le debug - a virer /!\//

Pistol::Pistol(Entity *entity) :
  AComponent(entity, T_PISTOL, 1),
  fireRate_(0.1),
  friction_(0.3),
  speedBullet_(10),
  bulletLifeTime_(3),
  shootTime_(al_get_time())
{
}

Pistol::~Pistol()
{
  // todo clear la pool provisoire - ca leak ^^ /!\ //
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
	  CollisionManager::getInstance()->remove(*it);
	  delete *it;
	  it = this->list_.erase(it);
	}
      else
	{
	  CollisionManager::getInstance()->add(*it);
	  ++it;
	}
    }
}

void					Pistol::draw()
{
  std::vector<Entity*>::iterator	it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      DrawManager::getInstance()->add(*it);
      ++it;
    }
}

bool					Pistol::fire(float vx, float vy)
{
  if (al_get_time() - this->shootTime_ < this->fireRate_)
    return false;

  Entity				*tmp;

  // todo /!\ le relier a l entity manager //
  tmp = new Entity;
  if (!tmp)
    return false;
  POSITION(tmp)->setPos(BOUNDING_BOX(this->entity)->getCenterX() - 15, BOUNDING_BOX(this->entity)->getCenterY() - 15, 3);
  MOVE(tmp)->setDirection(vx * this->speedBullet_, vy * this->speedBullet_);
  MOVE(tmp)->setFriction(this->friction_, this->friction_);
  VISIBILITY(tmp)->fadeOut(0.3, 10);
  IMAGE(tmp)->setBitmap("assets/imgs/bullet.png");
  ROTATION_FORCE(tmp)->launch(0.5, 0.005);
  FORCE_RESISTANCE(tmp)->setResistance(1);
  BOUNDING_BOX(tmp)->setDimension(24, 24);
  BOUNDING_BOX(tmp)->setMargin(3, 3);
  DAMAGE(tmp)->setMagnitude(5);
  DAMAGE(tmp)->setDamageNb(1);
  DANGER_TYPE(tmp)->setType(GOOD);
  COLLISION_TYPE(tmp)->setType(BULLET);
  *TEXT(tmp) = "bullet";

  this->shootTime_ = al_get_time();
  this->list_.push_back(tmp);
  return true;
}

void					Pistol::serialize(std::ofstream *file)
{
  int					type = T_PISTOL;

  file->write(reinterpret_cast<const char *>(&type), sizeof(type));
  file->write(reinterpret_cast<const char *>(&this->fireRate_), sizeof(double));
  file->write(reinterpret_cast<const char *>(&this->friction_), sizeof(double));
  file->write(reinterpret_cast<const char *>(&this->speedBullet_), sizeof(double));
  file->write(reinterpret_cast<const char *>(&this->bulletLifeTime_), sizeof(double));
}

void					Pistol::unserialize(std::ifstream *file)
{
  file->read(reinterpret_cast<char *>(&this->fireRate_), sizeof(double));
  file->read(reinterpret_cast<char *>(&this->friction_), sizeof(double));
  file->read(reinterpret_cast<char *>(&this->speedBullet_), sizeof(double));
  file->read(reinterpret_cast<char *>(&this->bulletLifeTime_), sizeof(double));
}
