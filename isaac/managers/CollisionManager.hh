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
private:
  CollisionManager();			// private ctor because of singleton pattern
};

#endif					// __COLLISION_MANAGER_H__
