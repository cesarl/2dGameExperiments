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
  virtual void				serialize(std::ofstream &file);
  virtual void				unserialize(std::ifstream &file);
  void					setDirection(double x, double y);
  void					setDirectionX(double x);
  void					setDirectionY(double y);
  void					incDirectionX(double x);
  void					incDirectionY(double y);
  void					setFriction(double x, double y);
  double				getDirectionX() const;
  double				getDirectionY() const;
  double				getDirection() const;
  void					reverseOneAxe(int x, int y, double multiply = 1);
  void					setMaxSpeed(double val);
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
  double				maxSpeed_;
};

#endif					// __MOVE_HH__
