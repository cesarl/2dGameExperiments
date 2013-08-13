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
  virtual void				serialize(std::ofstream &file);
  virtual void				unserialize(std::ifstream &file);
  int					getX() const;
  void					setPos(double x, double y, double z = 0.0f);
  void					reversePos();
public:
  double				x;
  double				y;
  double				z;
private:
  double				postx_;
  double				posty_;
};

#endif					// __POSITION_HH__
