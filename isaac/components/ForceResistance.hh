#ifndef					__FORCE_RESISTANCE_HH__
# define				__FORCE_RESISTANCE_HH__

#include				<math.h>
#include				"Component.hh"
#include				"Entity.hh"

class					ForceResistance : public AComponent
{
public:
  ForceResistance(Entity *entity);
  virtual ~ForceResistance();
  virtual void				update(double time = 0);
  virtual void				draw();
  virtual void				serialize(std::ofstream &file);
  virtual void				unserialize(std::ifstream &file);
  void					setResistance(double resistance);
  double				getResistance() const;
  void					applyForce(Entity *o);
private:
  double				resistance_;
};

#endif					// __FORCE_RESISTANCE_HH__
