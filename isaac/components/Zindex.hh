#ifndef					__ZINDEX_HH__
# define				__ZINDEX_HH__

#include				"Component.hh"
#include				"Entity.hh"

class					Zindex : public AComponent
{
public:
  Zindex(Entity *entity);
  virtual ~Zindex();
  virtual void				update(double time = 0);
  virtual void				draw();
  int					getIndex() const;
  void					setIndex();
private:
  int					z_;
};

#endif					// __ZINDEX_HH__
