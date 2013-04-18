#ifndef					__DEATH_HH__
# define				__DEATH_HH__

#include				"Component.hh"
#include				"Entity.hh"

class					Death : public AComponent
{
public:
  Death(Entity *entity);
  virtual ~Death();
  virtual void				update(double time = 0);
  virtual void				draw();
  bool					isDead() const;
  void					setDead(bool dead);
  virtual void				kill();
protected:
  bool					dead_;
};

#endif					// __DEATH_HH__
