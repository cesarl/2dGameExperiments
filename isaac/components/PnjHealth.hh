#ifndef					__PNJ_HEALTH_HH__
# define				__PNJ_HEALTH_HH__

#include				"Health.hh"

class					PnjHealth : public Health
{
public:
  PnjHealth(Entity *entity);
  virtual ~PnjHealth();
  virtual void				impactDamage(Entity *e);
};

#endif					// __PNJ_HEALTH_HH__
