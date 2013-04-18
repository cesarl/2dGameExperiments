#ifndef					__COLLISION_TYPE_HH__
# define				__COLLISION_TYPE_HH__

#include				"Component.hh"
#include				"Entity.hh"

typedef enum				t_collisionType
  {
    COL_NONE,
    BULLET,
    ACTOR,
    FIX_GO,
    DESTRUCTIBLE_GO
  }					t_collisionType;

class					CollisionType : public AComponent
{
public:
  CollisionType(Entity *entity);
  virtual ~CollisionType();
  virtual void				update(double time = 0);
  virtual void				draw();
  t_collisionType			getType() const;
  void					setType(t_collisionType type);
private:
  t_collisionType			type_;
};

#endif					// __COLLISION_TYPE_HH__
