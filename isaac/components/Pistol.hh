#ifndef					__PISTOL_HH__
# define				__PISTOL_HH__

#include				"Component.hh"

// le vector est provisoir - a terme les pistols seront relies a des entity pools et a des components pools


class					Pistol : public AComponent
{
public:
  Pistol(Entity *entity);
  virtual ~Pistol();
  virtual void				update(double time = 0);
  virtual void				draw();
  virtual void				serialize(std::ofstream &file);
  virtual void				unserialize(std::ifstream &file);
  bool					fire(float vx, float vy);
private:
  double				fireRate_;
  double				friction_;
  double				speedBullet_;
  double				bulletLifeTime_;
  double				shootTime_;
};

#endif					// __PISTOL_HH__
