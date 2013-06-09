#ifndef					__ROTATION_HH__
# define				__ROTATION_HH__

#include				"Component.hh"
#include				"Entity.hh"

class					Rotation : public AComponent
{
public:
  Rotation(Entity *entity);
  virtual ~Rotation();
  virtual void				update(double time = 0);
  virtual void				draw();
  virtual void				serialize(std::ofstream &file);
  virtual void				unserialize(std::ifstream &file);
public:
  float					angle;
};

#endif					// __ROTATION_HH__
