#include				<math.h>
#include				"RotationForce.hh"
#include				"ComponentTypes.hh"

RotationForce::RotationForce(Entity *entity) : AComponent(entity, T_ROTATION_FORCE, 1)
{
  ROTATION(entity);
  this->force_ = 0;
  this->friction_ = 0;
  this->direction_ = 0;
}

RotationForce::~RotationForce()
{}

void					RotationForce::update(double time)
{
  if (this->updateTimestamp == time || this->force_ == 0)
    return;
  this->updateTimestamp = time;
  this->force_ -= this->friction_;
  if (this->force_ <= 0)
    this->force_ = 0;
  ROTATION(this->entity)->angle += this->force_ * this->direction_;
}

void					RotationForce::draw()
{}

void					RotationForce::launch(double force, double friction)
{
  this->force_ = fabs(force);
  this->friction_ = friction;
  this->direction_ = force < 0 ? -1 : 1;
}

void					RotationForce::stop()
{
  this->force_ = 0;
  this->friction_ = 0;
  this->direction_ = 0;
}

void					RotationForce::serialize(std::ofstream *file)
{
  int					type = T_ROTATION_FORCE;

  file->write(reinterpret_cast<const char *>(&type), sizeof(type));
  file->write(reinterpret_cast<const char *>(&this->force_), sizeof(double));
  file->write(reinterpret_cast<const char *>(&this->friction_), sizeof(double));
  file->write(reinterpret_cast<const char *>(&this->direction_), sizeof(int));
}

void					RotationForce::unserialize(std::ifstream *file)
{
  file->read(reinterpret_cast<char *>(&this->force_), sizeof(double));
  file->read(reinterpret_cast<char *>(&this->friction_), sizeof(double));
  file->read(reinterpret_cast<char *>(&this->direction_), sizeof(int));
}
