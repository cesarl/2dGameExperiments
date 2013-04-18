#ifndef					__PNJ_HH__
# define				__PNJ_HH__

#include				"Entity.hh"

class					Pnj : public Entity
{
public:
  Pnj();
  virtual ~Pnj();
  virtual void				generate(int seed = 0);
};

#endif					// __PNJ_HH__
