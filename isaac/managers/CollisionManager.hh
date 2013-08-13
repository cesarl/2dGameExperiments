#ifndef					__COLLISION__MANAGER_H__
# define				__COLLISION_MANAGER_H__

#include				<vector>
#include				"ComponentTypes.hh"
#include				"CollisionType.hh"
#include				"DangerType.hh"

class					CollisionManager
{
public:
  ~CollisionManager();
  static CollisionManager		*getInstance();
  void					resolveCollision(Entity *e1, Entity *e2);
  void					update();
  void					add(Entity *entity);
  void					remove(Entity *entity);
  void					clear();
private:
  int					cellSize_;
  int					height_;
  int					width_;
  int					maxWidth_;
  std::map< int, std::list<Entity*> >	list_;
  CollisionManager();			// private ctor because of singleton pattern
  typedef				std::map < int, std::list<Entity*> >::iterator t_cell_iter;
  typedef				std::list<Entity*>::iterator t_iter;
};

#endif					// __COLLISION_MANAGER_H__
