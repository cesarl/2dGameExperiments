#include				"Pnj.hh"
#include				"ComponentTypes.hh"

Pnj::Pnj() : Entity()
{}

Pnj::~Pnj()
{}
void					Pnj::generate(int seed)
{
  if (seed != 0)
    this->seed_ = seed;
  srand(this->seed_);
  SPRITE(this)->config(8, 64, 64, 8, 8, 8, 0.12);
  IMAGE(this)->setBitmap("assets/imgs/mummy.png");
  FORCE_RESISTANCE(this)->setResistance(1);
  MOVE(this)->setFriction(0.07, 0.07);
  BOUNDING_BOX(this)->setDimension(30, 30);
  BOUNDING_BOX(this)->setMargin(17, 17);
  DAMAGE(this)->setMagnitude(3);
  DAMAGE(this)->setDamageNb(-1);
  HEALTH(this)->setHealth(10);
  DANGER_TYPE(this)->setType(BAD);
  COLLISION_TYPE(this)->setType(ACTOR);
  PNJ_DEATH(this);
  *TEXT(this) = "mommy";
  (void)seed;
}
