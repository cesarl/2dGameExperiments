#ifndef					__DRAW_MANAGER_H__
# define				__DRAW_MANAGER_H__

#include				"Entity.hh"
#include				"ComponentTypes.hh"
#include				<map>

class					DrawManager
{
public:
  ~DrawManager();
  static DrawManager			*getInstance();
  void					clear();
  void					draw(ALLEGRO_EVENT *event = NULL);
  void					add(Entity *entity, int layer = 0);
private:
  std::multimap<unsigned long, Entity*>		go_;
  DrawManager();			// private ctor because of singleton pattern
};

#endif					// __DRAW_MANAGER_H__
