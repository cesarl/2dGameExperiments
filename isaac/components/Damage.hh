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
  void					setMagnitude(int magnitude);
  void					setDamageNb(int damageNb);
  int					getMagnitude() const;
  int					getDamageNb() const;
  void					applied();
private:
  int					magnitude_;
  int					damageNb_;
};

#endif					// __DAMAGE_HH__
