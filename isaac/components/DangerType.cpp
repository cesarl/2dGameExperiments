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

void					DangerType::serialize(std::ofstream *file)
{
  int					type = T_DANGER_TYPE;
  int					coltype = this->type_;

  file->write(reinterpret_cast<const char *>(&type), sizeof(type));
  file->write(reinterpret_cast<const char *>(&coltype), sizeof(int));
}

void					DangerType::unserialize(std::ifstream *file)
{
  int t;
  file->read(reinterpret_cast<char *>(&t), sizeof(int));
  this->type_ = (t_dangerType)t;
}
