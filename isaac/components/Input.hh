#ifndef					__INPUT_HH__
# define				__INPUT_HH__

#include				"Component.hh"
#include				"Entity.hh"

class					EventManager;

class					Input : public AComponent
{
public:
  Input(Entity *entity);
  virtual ~Input();
  virtual void				update(double time = 0);
  virtual void				draw();
  virtual void				serialize(std::ofstream *file);
  void					inputEvent(ALLEGRO_EVENT * event);
  void					listen(bool value);
public:
  bool					up;
  bool					down;
  bool					left;
  bool					right;
  bool					space;
  bool					sup;
  bool					sdown;
  bool					sleft;
  bool					sright;
};

#endif					// __INPUT_HH__
