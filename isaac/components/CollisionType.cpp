#include				"CollisionType.hh"
#include				"ComponentTypes.hh"

CollisionType::CollisionType(Entity *entity) : AComponent(entity, T_COLLISION_TYPE),
					       type_(COL_NONE)
{
}

CollisionType::~CollisionType()
{}

t_collisionType				CollisionType::getType() const
{
  return this->type_;
}

void					CollisionType::setType(t_collisionType type)
{
  this->type_ = type;
}

void					CollisionType::update(double time)
{
  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;
}

void					CollisionType::draw()
{}
