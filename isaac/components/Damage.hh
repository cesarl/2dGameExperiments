#ifndef					__DAMAGE_HH__
# define				__DAMAGE_HH__

#include				"Component.hh"
#include				"Entity.hh"

class					Damage : public AComponent
{
public:
  Damage(Entity *entity);
  virtual ~Damage();
  virtual void				update(double time = 0);
  virtual void				draw();
  virtual void				serialize(std::ofstream &file);
  virtual void				unserialize(std::ifstream &file);
  void					setMagnitude(int magnitude);
  void					setDamageNb(int damageNb);
  void					setDelay(double delay);
  int					getMagnitude() const;
  int					getDamageNb() const;
  bool					canDamage() const;
  virtual void				applied();
private:
  int					magnitude_;
  int					damageNb_;
  double				delay_;
  double				delayCounter_;
};

#endif					// __DAMAGE_HH__
