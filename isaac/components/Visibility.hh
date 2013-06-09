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
  virtual void				serialize(std::ofstream &file);
  virtual void				unserialize(std::ifstream &file);
  void					fadeOut(double speed, unsigned int ratio = 3);
  void					fadeIn(double speed, unsigned int ratio = 3);
  void					setVisible(bool value);
  void					blink(int nb, double speed);
public:
  bool					visible;
  int					opacity;
private:
  double				timeCounter_;
  int					fade_;
  double				speed_;
  double				blinkSpeed_;
  int					blinkNb_;
  int					blinkCounter_;
  int					blinkTimeCounter_;
};

#endif					// __VISIBILITY_HH__
