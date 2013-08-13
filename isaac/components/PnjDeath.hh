#ifndef					__PNJ_DEATH_HH__
# define				__PNJ_DEATH_HH__

#include				"Death.hh"

class					PnjDeath : public Death
{
public:
  PnjDeath(Entity *entity);
  virtual ~PnjDeath();
  virtual void				update(double time = 0);
  virtual void				draw();
  // virtual void				serialize(std::ofstream *file);
  bool					isDead() const;
  void					setDead(bool dead);
  virtual void				kill();
};

#endif					// __PNJ_DEATH_HH__
