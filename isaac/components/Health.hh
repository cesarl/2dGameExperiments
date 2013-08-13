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
  virtual void				serialize(std::ofstream &file);
  virtual void				unserialize(std::ifstream &file);
  void					setHealth(int health);
  int					getHealth() const;
  virtual void				impactDamage(Entity *e);
  void					setDelay(double delay);
protected:
  int					health_;
  double				delay_;
  double				delayCounter_;
};

#endif					// __HEALTH_HH__
