#ifndef					__TEXT_INPUT_HH__
# define				__TEXT_INPUT_HH__

#include				"Component.hh"
#include				"Entity.hh"

class					TextInput : public AComponent
{
public:
  TextInput(Entity *entity);
  virtual ~TextInput();
  virtual void				update(double time = 0);
  virtual void				draw();
  void					input(ALLEGRO_EVENT *event);
};

#endif					// __TEXT_INPUT_HH__
