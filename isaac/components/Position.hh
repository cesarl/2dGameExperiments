#ifndef					__POSITION_HH__
# define				__POSITION_HH__

#include				"Component.hh"
#include				"Entity.hh"

class					Position : public AComponent
{
public:
  Position(Entity *entity);
  virtual ~Position();
  virtual void				update(double time = 0);
  virtual void				draw();
  int					getX() const;
  void					setPos(double x, double y);
  void					reversePos();
public:
  double				x;
  double				y;
private:
  double				postx_;
  double				posty_;
};

#endif					// __POSITION_HH__
