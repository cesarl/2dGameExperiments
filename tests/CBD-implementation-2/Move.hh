#ifndef					__MOVE_HH__
# define				__MOVE_HH__

#include				"Component.hh"
#include				"Entity.hh"

class					Move : public AComponent
{
public:
  Move(Entity *entity);
  virtual ~Move();
  virtual void				update(double time = 0);
  virtual void				draw();
public:
  double				vx;
  double				vy;
  double				gravityX;
  double				gravityY;
  double				frictionX;
  double				frictionY;
};

#endif					// __MOVE_HH__
