#ifndef					__HEROS_HH__
# define				__HEROS_HH__

#include				"Component.hh"
#include				"Entity.hh"

class					Heros : public AComponent
{
public:
  Heros(Entity *entity);
  virtual ~Heros();
  virtual void				update(double time = 0);
  virtual void				draw();
  virtual void				serialize(std::ofstream *file);
private:
};

#endif					// __HEROs_HH__
