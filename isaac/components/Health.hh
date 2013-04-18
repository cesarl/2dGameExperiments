#ifndef					__HEALTH_HH__
# define				__HEALTH_HH__

#include				"Component.hh"
#include				"Entity.hh"

class					Health : public AComponent
{
public:
  Health(Entity *entity);
  virtual ~Health();
  virtual void				update(double time = 0);
  virtual void				draw();
  void					setHealth(int health);
  int					getHealth() const;
  void					impactDamage(Entity *e);
private:
  int					health_;
};

#endif					// __HEALTH_HH__
