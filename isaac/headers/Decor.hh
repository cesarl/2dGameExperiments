#ifndef					__DECOR_HH__
# define				__DECOR_HH__

#include				"Entity.hh"

class					Decor : public Entity
{
public:
  Decor();
  virtual ~Decor();
  virtual void				serialize(std::ofstream *file);
  virtual void				unserialize(std::ifstream *file);
  virtual void				generate(int seed = 0);
};

#endif					// __DECOR_HH__
