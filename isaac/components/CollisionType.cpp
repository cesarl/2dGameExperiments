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

void					CollisionType::serialize(std::ofstream &file)
{
  int					type = T_COLLISION_TYPE;
  int					coltype = this->type_;

  Archive::serialize(file, type);
  Archive::serialize(file, coltype);
}

void					CollisionType::unserialize(std::ifstream &file)
{
  Archive::unserialize(file, this->type_);
}
