#include				"DangerType.hh"
#include				"ComponentTypes.hh"

DangerType::DangerType(Entity *entity) : AComponent(entity, T_DANGER_TYPE),
					 type_(DAN_NONE)
{
}

DangerType::~DangerType()
{}

t_dangerType				DangerType::getType() const
{
  return this->type_;
}

void					DangerType::setType(t_dangerType type)
{
  this->type_ = type;
}

void					DangerType::update(double time)
{
  if (this->updateTimestamp == time)
    return;
  this->updateTimestamp = time;
}

void					DangerType::draw()
{}
