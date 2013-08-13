#ifndef					__VISIBILITY_HH__
# define				__VISIBILITY_HH__

#include				"Component.hh"
#include				"Entity.hh"

class					Visibility : public AComponent
{
public:
  Visibility(Entity *entity);
  virtual ~Visibility();
  virtual void				update(double time = 0);
  virtual void				draw();
  void					fadeOut(double speed, unsigned int ratio = 3);
  void					fadeIn(double speed, unsigned int ratio = 3);
  void					setVisible(bool value);
public:
  bool					visible;
  int					opacity;
private:
  double				timeCounter_;
  int					fade_;
  double				speed_;
};

#endif					// __VISIBILITY_HH__
