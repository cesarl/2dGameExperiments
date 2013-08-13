#ifndef					__ROTATION_FORCE_HH__
# define				__ROTATION_FORCE_HH__

#include				"Component.hh"
#include				"Entity.hh"

class					RotationForce : public AComponent
{
public:
  RotationForce(Entity *entity);
  virtual ~RotationForce();
  virtual void				update(double time = 0);
  virtual void				draw();
  virtual void				serialize(std::ofstream &file);
  virtual void				unserialize(std::ifstream &file);
  void					launch(double force, double friction);
  void					stop();
private:
  double				force_;
  double				friction_;
  int					direction_;
};

#endif					// __ROTATION_FORCE_HH__
