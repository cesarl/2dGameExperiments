#include				"Pistol.hh"
#include				"ComponentTypes.hh"
#include				"EntityManager.hh"

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
}

void					Pistol::draw()
{
}

bool					Pistol::fire(float vx, float vy)
{
  if (al_get_time() - this->shootTime_ < this->fireRate_)
    return false;

  Entity				*tmp;

  tmp = EntityManager::getInstance()->create();
  if (!tmp)
    return false;
  POSITION(tmp)->setPos(BOUNDING_BOX(this->entity)->getCenterX() - 15, BOUNDING_BOX(this->entity)->getCenterY() - 15, 3);
  MOVE(tmp)->setDirection(vx * this->speedBullet_, vy * this->speedBullet_);
  MOVE(tmp)->setFriction(this->friction_, this->friction_);
  VISIBILITY(tmp)->fadeOut(0.3, 10);
  VISIBILITY(tmp)->invisibleKill(true);
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
  return true;
}

void					Pistol::serialize(std::ofstream &file)
{
  int					type = T_PISTOL;

  Archive::serialize(file, type);
  Archive::serialize(file, this->fireRate_);
  Archive::serialize(file, this->friction_);
  Archive::serialize(file, this->speedBullet_);
  Archive::serialize(file, this->bulletLifeTime_);
}

void					Pistol::unserialize(std::ifstream &file)
{
  Archive::unserialize(file, this->fireRate_);
  Archive::unserialize(file, this->friction_);
  Archive::unserialize(file, this->speedBullet_);
  Archive::unserialize(file, this->bulletLifeTime_);
}
