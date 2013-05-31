#ifndef					__SPRITE_HH__
# define				__SPRITE_HH__

#include				"Component.hh"
#include				"Entity.hh"

class					Sprite : public AComponent
{
public:
  Sprite(Entity *entity);
  virtual ~Sprite();
  virtual void				update(double time = 0);
  virtual void				draw();
  virtual void				serialize(std::ofstream *file);
  virtual void				unserialize(std::ifstream *file);
  void					config(int columnNumber,
					       int partWidth,
					       int partHeight,
					       unsigned int from,
					       unsigned int stepNumber,
					       unsigned int currentStep,
					       double speed);
public:
  int					columnNumber;
  int					partWidth;
  int					partHeight;
  unsigned int				from;
  unsigned int				stepNumber;
  unsigned int				currentStep;
  double				speed;
private:
  double				timeCounter_;
};

#endif					// __SPRITE_HH__
