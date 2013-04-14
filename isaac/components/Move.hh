#ifndef					__MOVE_HH__
# define				__MOVE_HH__

#include				<math.h>
#include				"Component.hh"
#include				"Entity.hh"

class					Move : public AComponent
{
public:
  Move(Entity *entity);
  virtual ~Move();
  virtual void				update(double time = 0);
  virtual void				draw();
  void					setDirection(double x, double y);
  void					setDirectionX(double x);
  void					setDirectionY(double y);
  void					setFriction(double x, double y);
  double				getDirectionX() const;
  double				getDirectionY() const;
  double				getDirection() const;
  void					reverseOneAxe(int x, int y, double multiply = 1);
public:
  double				vx;
  double				vy;
  double				gravityX;
  double				gravityY;
  double				frictionX;
  double				frictionY;
private:
  int					dirX_;
  int					dirY_;
};

#endif					// __MOVE_HH__
