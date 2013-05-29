#ifndef					__PISTOL_HH__
# define				__PISTOL_HH__

#include				<vector>
#include				"Component.hh"
#include				"Entity.hh"

// le vector est provisoir - a terme les pistols seront relies a des entity pools et a des components pools

class					Grid;
class					DrawCollection;

class					Pistol : public AComponent
{
public:
  Pistol(Entity *entity);
  virtual ~Pistol();
  virtual void				update(double time = 0);
  virtual void				draw();
  bool					fire(float vx, float vy);
  void					attachGridCollision(Grid *grid);
private:
  double				fireRate_;
  double				friction_;
  double				speedBullet_;
  double				bulletLifeTime_;
  double				shootTime_;
  Grid					*gridCollision_;
  std::vector<Entity*>			list_;
};

#endif					// __PISTOL_HH__